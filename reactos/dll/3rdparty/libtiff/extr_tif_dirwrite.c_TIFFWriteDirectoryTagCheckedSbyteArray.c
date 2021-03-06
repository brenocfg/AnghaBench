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
typedef  int /*<<< orphan*/  int8 ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int TIFFWriteDirectoryTagData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFF_SBYTE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagCheckedSbyteArray(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 count, int8* value)
{
	assert(sizeof(int8)==1);
	return(TIFFWriteDirectoryTagData(tif,ndir,dir,tag,TIFF_SBYTE,count,count,value));
}