#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_5__ {scalar_t__ td_planarconfig; int /*<<< orphan*/  td_samplesperpixel; int /*<<< orphan*/  td_imagewidth; int /*<<< orphan*/  td_bitspersample; } ;
struct TYPE_6__ {TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ PLANARCONFIG_CONTIG ; 
 int /*<<< orphan*/  TIFFhowmany8_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _TIFFMultiply64 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

uint64
TIFFRasterScanlineSize64(TIFF* tif)
{
	static const char module[] = "TIFFRasterScanlineSize64";
	TIFFDirectory *td = &tif->tif_dir;
	uint64 scanline;

	scanline = _TIFFMultiply64(tif, td->td_bitspersample, td->td_imagewidth, module);
	if (td->td_planarconfig == PLANARCONFIG_CONTIG) {
		scanline = _TIFFMultiply64(tif, scanline, td->td_samplesperpixel, module);
		return (TIFFhowmany8_64(scanline));
	} else
		return (_TIFFMultiply64(tif, TIFFhowmany8_64(scanline),
		    td->td_samplesperpixel, module));
}