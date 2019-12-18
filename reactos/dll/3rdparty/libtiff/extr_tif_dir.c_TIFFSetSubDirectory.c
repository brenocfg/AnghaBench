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
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_4__ {scalar_t__ tif_dirnumber; int /*<<< orphan*/  tif_nextdiroff; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int TIFFReadDirectory (TYPE_1__*) ; 

int
TIFFSetSubDirectory(TIFF* tif, uint64 diroff)
{
	tif->tif_nextdiroff = diroff;
	/*
	 * Reset tif_dirnumber counter and start new list of seen directories.
	 * We need this to prevent IFD loops.
	 */
	tif->tif_dirnumber = 0;
	return (TIFFReadDirectory(tif));
}