#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FONScontext ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FONS_INVALID ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fonsAddFontMem (int /*<<< orphan*/ *,char const*,unsigned char*,int,int) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 

int fonsAddFont(FONScontext* stash, const char* name, const char* path)
{
	FILE* fp = 0;
	int dataSize = 0;
	unsigned char* data = NULL;

	// Read in the font data.
	fp = fopen(path, "rb");
	if (fp == NULL) goto error;
	fseek(fp,0,SEEK_END);
	dataSize = (int)ftell(fp);
	fseek(fp,0,SEEK_SET);
	data = (unsigned char*)malloc(dataSize);
	if (data == NULL) goto error;
	fread(data, 1, dataSize, fp);
	fclose(fp);
	fp = 0;

	return fonsAddFontMem(stash, name, data, dataSize, 1);

error:
	if (data) free(data);
	if (fp) fclose(fp);
	return FONS_INVALID;
}