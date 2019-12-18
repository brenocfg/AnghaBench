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
struct TYPE_5__ {int tif_flags; int /*<<< orphan*/  (* tif_postencode ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int TIFFFlushData1 (TYPE_1__*) ; 
 int TIFF_BEENWRITING ; 
 int TIFF_POSTENCODE ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

int
TIFFFlushData(TIFF* tif)
{
	if ((tif->tif_flags & TIFF_BEENWRITING) == 0)
		return (1);
	if (tif->tif_flags & TIFF_POSTENCODE) {
		tif->tif_flags &= ~TIFF_POSTENCODE;
		if (!(*tif->tif_postencode)(tif))
			return (0);
	}
	return (TIFFFlushData1(tif));
}