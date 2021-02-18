// m3ugen.cpp : lists .mp3 files in a directory, and lists them to
//              a .m3u file.

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// Try and get current directory
	char dirpath[MAX_PATH];
	int pathcount = GetCurrentDirectory(MAX_PATH-1,dirpath);

	if(pathcount)
	{
		// do the funky stuff
		while(*(dirpath+pathcount)!=92)
			pathcount--;

		char* dirname = dirpath+pathcount+1;
		sprintf(dirpath,"%s.m3u",dirname);

	} else {
		// failsafe
		sprintf(dirpath,"playlist.m3u");
	}

	WIN32_FIND_DATA fileinfo;
	HANDLE searchHand = FindFirstFile("*.mp3",&fileinfo);
	
	if(searchHand!=INVALID_HANDLE_VALUE)
	{
		FILE* output;
		output=fopen(dirpath,"w");

		while(searchHand!=INVALID_HANDLE_VALUE)
		{
			if(fileinfo.dwFileAttributes!=FILE_ATTRIBUTE_DIRECTORY)
				fprintf(output,"%s\n",fileinfo.cFileName);

			if(!FindNextFile(searchHand,&fileinfo))
			{
				FindClose(searchHand);
				searchHand=INVALID_HANDLE_VALUE;
			}
		}

		fclose(output);

	} else {

		MessageBoxEx(NULL,"Can't find anything to do in this directory :/\n\nCopy m3ugen to a directory with mp3 files\nand run it again, dumbarse.\n\nYou smell :(","m3ugen error",MB_OK+MB_ICONSTOP,LANG_ENGLISH);
	}

	return 0;
}



