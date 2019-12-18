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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_4__ {int tif_flags; int /*<<< orphan*/  tif_clientdata; } ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  TIFFSwabArrayOfLong8 (int /*<<< orphan*/ *,int) ; 
 int TIFFWriteDirectoryTagData (TYPE_1__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int TIFF_BIGTIFF ; 
 int /*<<< orphan*/  TIFF_SLONG8 ; 
 int TIFF_SWAB ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagCheckedSlong8Array(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 count, int64* value)
{
	assert(count<0x20000000);
	assert(sizeof(int64)==8);
	if( !(tif->tif_flags&TIFF_BIGTIFF) ) {
		TIFFErrorExt(tif->tif_clientdata,"TIFFWriteDirectoryTagCheckedSlong8Array","SLONG8 not allowed for ClassicTIFF");
		return(0);
	}
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabArrayOfLong8((uint64*)value,count);
	return(TIFFWriteDirectoryTagData(tif,ndir,dir,tag,TIFF_SLONG8,count,count*8,value));
}