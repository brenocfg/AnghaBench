#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  scalar_t__ uint16 ;
struct TYPE_4__ {int td_rowsperstrip; scalar_t__ td_planarconfig; scalar_t__ td_samplesperpixel; int td_stripsperimage; } ;
struct TYPE_5__ {int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ PLANARCONFIG_SEPARATE ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,unsigned long,unsigned long) ; 

uint32
TIFFComputeStrip(TIFF* tif, uint32 row, uint16 sample)
{
	static const char module[] = "TIFFComputeStrip";
	TIFFDirectory *td = &tif->tif_dir;
	uint32 strip;

	strip = row / td->td_rowsperstrip;
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE) {
		if (sample >= td->td_samplesperpixel) {
			TIFFErrorExt(tif->tif_clientdata, module,
			    "%lu: Sample out of range, max %lu",
			    (unsigned long) sample, (unsigned long) td->td_samplesperpixel);
			return (0);
		}
		strip += (uint32)sample*td->td_stripsperimage;
	}
	return (strip);
}