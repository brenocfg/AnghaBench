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
typedef  scalar_t__ uint64 ;
typedef  size_t uint16 ;
struct TYPE_4__ {int tif_dirnumber; scalar_t__* tif_dirlist; int tif_dirlistsize; int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ _TIFFCheckRealloc (TYPE_1__*,scalar_t__*,int,int,char*) ; 

__attribute__((used)) static int
TIFFCheckDirOffset(TIFF* tif, uint64 diroff)
{
	uint16 n;

	if (diroff == 0)			/* no more directories */
		return 0;
	if (tif->tif_dirnumber == 65535) {
	    TIFFErrorExt(tif->tif_clientdata, "TIFFCheckDirOffset",
			 "Cannot handle more than 65535 TIFF directories");
	    return 0;
	}

	for (n = 0; n < tif->tif_dirnumber && tif->tif_dirlist; n++) {
		if (tif->tif_dirlist[n] == diroff)
			return 0;
	}

	tif->tif_dirnumber++;

	if (tif->tif_dirlist == NULL || tif->tif_dirnumber > tif->tif_dirlistsize) {
		uint64* new_dirlist;

		/*
		 * XXX: Reduce memory allocation granularity of the dirlist
		 * array.
		 */
		new_dirlist = (uint64*)_TIFFCheckRealloc(tif, tif->tif_dirlist,
		    tif->tif_dirnumber, 2 * sizeof(uint64), "for IFD list");
		if (!new_dirlist)
			return 0;
		if( tif->tif_dirnumber >= 32768 )
		    tif->tif_dirlistsize = 65535;
		else
		    tif->tif_dirlistsize = 2 * tif->tif_dirnumber;
		tif->tif_dirlist = new_dirlist;
	}

	tif->tif_dirlist[tif->tif_dirnumber - 1] = diroff;

	return 1;
}