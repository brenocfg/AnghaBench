#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_5__ {int tif_flags; } ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFCvtNativeToIEEEFloat (TYPE_1__*,int,float**) ; 
 int /*<<< orphan*/  TIFFSwabArrayOfFloat (float*,int) ; 
 int TIFFWriteDirectoryTagData (TYPE_1__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,float*) ; 
 int /*<<< orphan*/  TIFF_FLOAT ; 
 int TIFF_SWAB ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagCheckedFloatArray(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 count, float* value)
{
	assert(count<0x40000000);
	assert(sizeof(float)==4);
	TIFFCvtNativeToIEEEFloat(tif,count,&value);
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabArrayOfFloat(value,count);
	return(TIFFWriteDirectoryTagData(tif,ndir,dir,tag,TIFF_FLOAT,count,count*4,value));
}