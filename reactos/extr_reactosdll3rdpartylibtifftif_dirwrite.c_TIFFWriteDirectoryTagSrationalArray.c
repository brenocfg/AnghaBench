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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int TIFFWriteDirectoryTagCheckedSrationalArray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagSrationalArray(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 count, float* value)
{
	if (dir==NULL)
	{
		(*ndir)++;
		return(1);
	}
	return(TIFFWriteDirectoryTagCheckedSrationalArray(tif,ndir,dir,tag,count,value));
}