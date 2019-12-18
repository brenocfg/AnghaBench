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
typedef  scalar_t__ uint32 ;
struct TYPE_5__ {scalar_t__ td_tilewidth; scalar_t__ td_tilelength; scalar_t__ td_tiledepth; scalar_t__ td_imagewidth; scalar_t__ td_imagelength; scalar_t__ td_imagedepth; scalar_t__ td_planarconfig; scalar_t__ td_samplesperpixel; } ;
struct TYPE_6__ {TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ PLANARCONFIG_SEPARATE ; 
 scalar_t__ TIFFhowmany_32 (scalar_t__,scalar_t__) ; 
 scalar_t__ _TIFFMultiply32 (TYPE_2__*,scalar_t__,scalar_t__,char*) ; 

uint32
TIFFNumberOfTiles(TIFF* tif)
{
	TIFFDirectory *td = &tif->tif_dir;
	uint32 dx = td->td_tilewidth;
	uint32 dy = td->td_tilelength;
	uint32 dz = td->td_tiledepth;
	uint32 ntiles;

	if (dx == (uint32) -1)
		dx = td->td_imagewidth;
	if (dy == (uint32) -1)
		dy = td->td_imagelength;
	if (dz == (uint32) -1)
		dz = td->td_imagedepth;
	ntiles = (dx == 0 || dy == 0 || dz == 0) ? 0 :
	    _TIFFMultiply32(tif, _TIFFMultiply32(tif, TIFFhowmany_32(td->td_imagewidth, dx),
	    TIFFhowmany_32(td->td_imagelength, dy),
	    "TIFFNumberOfTiles"),
	    TIFFhowmany_32(td->td_imagedepth, dz), "TIFFNumberOfTiles");
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE)
		ntiles = _TIFFMultiply32(tif, ntiles, td->td_samplesperpixel,
		    "TIFFNumberOfTiles");
	return (ntiles);
}