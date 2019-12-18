#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ uint16 ;
struct TYPE_8__ {scalar_t__ tiff_diroff; } ;
struct TYPE_9__ {scalar_t__ tiff_diroff; } ;
struct TYPE_10__ {TYPE_1__ big; TYPE_2__ classic; } ;
struct TYPE_11__ {int tif_flags; scalar_t__ tif_dirnumber; scalar_t__ tif_curdir; scalar_t__ tif_nextdiroff; TYPE_3__ tif_header; } ;
typedef  TYPE_4__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFAdvanceDirectory (TYPE_4__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int TIFFReadDirectory (TYPE_4__*) ; 
 int TIFF_BIGTIFF ; 

int
TIFFSetDirectory(TIFF* tif, uint16 dirn)
{
	uint64 nextdir;
	uint16 n;

	if (!(tif->tif_flags&TIFF_BIGTIFF))
		nextdir = tif->tif_header.classic.tiff_diroff;
	else
		nextdir = tif->tif_header.big.tiff_diroff;
	for (n = dirn; n > 0 && nextdir != 0; n--)
		if (!TIFFAdvanceDirectory(tif, &nextdir, NULL))
			return (0);
	tif->tif_nextdiroff = nextdir;
	/*
	 * Set curdir to the actual directory index.  The
	 * -1 is because TIFFReadDirectory will increment
	 * tif_curdir after successfully reading the directory.
	 */
	tif->tif_curdir = (dirn - n) - 1;
	/*
	 * Reset tif_dirnumber counter and start new list of seen directories.
	 * We need this to prevent IFD loops.
	 */
	tif->tif_dirnumber = 0;
	return (TIFFReadDirectory(tif));
}