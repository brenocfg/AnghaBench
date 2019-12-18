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
typedef  int uint64 ;
typedef  scalar_t__ uint32 ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 scalar_t__ STRIP_SIZE_DEFAULT ; 
 int TIFFScanlineSize64 (int /*<<< orphan*/ *) ; 

uint32
_TIFFDefaultStripSize(TIFF* tif, uint32 s)
{
	if ((int32) s < 1) {
		/*
		 * If RowsPerStrip is unspecified, try to break the
		 * image up into strips that are approximately
		 * STRIP_SIZE_DEFAULT bytes long.
		 */
		uint64 scanlinesize;
		uint64 rows;
		scanlinesize=TIFFScanlineSize64(tif);
		if (scanlinesize==0)
			scanlinesize=1;
		rows=(uint64)STRIP_SIZE_DEFAULT/scanlinesize;
		if (rows==0)
			rows=1;
		else if (rows>0xFFFFFFFF)
			rows=0xFFFFFFFF;
		s=(uint32)rows;
	}
	return (s);
}