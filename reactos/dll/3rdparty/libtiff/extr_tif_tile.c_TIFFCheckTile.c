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
typedef  int uint16 ;
struct TYPE_4__ {int td_imagewidth; int td_imagelength; int td_imagedepth; scalar_t__ td_planarconfig; int td_samplesperpixel; } ;
struct TYPE_5__ {int /*<<< orphan*/  tif_name; int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ PLANARCONFIG_SEPARATE ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 

int
TIFFCheckTile(TIFF* tif, uint32 x, uint32 y, uint32 z, uint16 s)
{
	TIFFDirectory *td = &tif->tif_dir;

	if (x >= td->td_imagewidth) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Col out of range, max %lu",
			     (unsigned long) x,
			     (unsigned long) (td->td_imagewidth - 1));
		return (0);
	}
	if (y >= td->td_imagelength) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Row out of range, max %lu",
			     (unsigned long) y,
			     (unsigned long) (td->td_imagelength - 1));
		return (0);
	}
	if (z >= td->td_imagedepth) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Depth out of range, max %lu",
			     (unsigned long) z,
			     (unsigned long) (td->td_imagedepth - 1));
		return (0);
	}
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE &&
	    s >= td->td_samplesperpixel) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Sample out of range, max %lu",
			     (unsigned long) s,
			     (unsigned long) (td->td_samplesperpixel - 1));
		return (0);
	}
	return (1);
}