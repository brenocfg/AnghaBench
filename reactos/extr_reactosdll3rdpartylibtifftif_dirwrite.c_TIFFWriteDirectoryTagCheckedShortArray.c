#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {int tif_flags; } ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFSwabArrayOfShort (int /*<<< orphan*/ *,int) ; 
 int TIFFWriteDirectoryTagData (TYPE_1__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFF_SHORT ; 
 int TIFF_SWAB ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagCheckedShortArray(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 count, uint16* value)
{
	assert(count<0x80000000);
	assert(sizeof(uint16)==2);
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabArrayOfShort(value,count);
	return(TIFFWriteDirectoryTagData(tif,ndir,dir,tag,TIFF_SHORT,count,count*2,value));
}