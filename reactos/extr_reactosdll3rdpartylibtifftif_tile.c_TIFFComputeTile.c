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
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ uint16 ;
struct TYPE_4__ {scalar_t__ td_tilewidth; scalar_t__ td_tilelength; scalar_t__ td_tiledepth; int td_imagedepth; scalar_t__ td_imagewidth; scalar_t__ td_imagelength; scalar_t__ td_planarconfig; } ;
struct TYPE_5__ {TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ PLANARCONFIG_SEPARATE ; 
 scalar_t__ TIFFhowmany_32 (scalar_t__,scalar_t__) ; 

uint32
TIFFComputeTile(TIFF* tif, uint32 x, uint32 y, uint32 z, uint16 s)
{
	TIFFDirectory *td = &tif->tif_dir;
	uint32 dx = td->td_tilewidth;
	uint32 dy = td->td_tilelength;
	uint32 dz = td->td_tiledepth;
	uint32 tile = 1;

	if (td->td_imagedepth == 1)
		z = 0;
	if (dx == (uint32) -1)
		dx = td->td_imagewidth;
	if (dy == (uint32) -1)
		dy = td->td_imagelength;
	if (dz == (uint32) -1)
		dz = td->td_imagedepth;
	if (dx != 0 && dy != 0 && dz != 0) {
		uint32 xpt = TIFFhowmany_32(td->td_imagewidth, dx);
		uint32 ypt = TIFFhowmany_32(td->td_imagelength, dy);
		uint32 zpt = TIFFhowmany_32(td->td_imagedepth, dz);

		if (td->td_planarconfig == PLANARCONFIG_SEPARATE) 
			tile = (xpt*ypt*zpt)*s +
			     (xpt*ypt)*(z/dz) +
			     xpt*(y/dy) +
			     x/dx;
		else
			tile = (xpt*ypt)*(z/dz) + xpt*(y/dy) + x/dx;
	}
	return (tile);
}