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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int TIFFWriteDirectoryTagCheckedLong (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int TIFFWriteDirectoryTagCheckedShort (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagShortLong(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 value)
{
	if (dir==NULL)
	{
		(*ndir)++;
		return(1);
	}
	if (value<=0xFFFF)
		return(TIFFWriteDirectoryTagCheckedShort(tif,ndir,dir,tag,(uint16)value));
	else
		return(TIFFWriteDirectoryTagCheckedLong(tif,ndir,dir,tag,value));
}