#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  int uint16 ;
struct TYPE_8__ {scalar_t__ tiff_diroff; } ;
struct TYPE_7__ {scalar_t__ tiff_diroff; } ;
struct TYPE_9__ {TYPE_2__ big; TYPE_1__ classic; } ;
struct TYPE_10__ {int tif_flags; int /*<<< orphan*/  tif_clientdata; TYPE_3__ tif_header; } ;
typedef  TYPE_4__ TIFF ;

/* Variables and functions */
 scalar_t__ TIFFAdvanceDirectory (TYPE_4__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 int TIFF_BIGTIFF ; 

uint16
TIFFNumberOfDirectories(TIFF* tif)
{
	static const char module[] = "TIFFNumberOfDirectories";
	uint64 nextdir;
	uint16 n;
	if (!(tif->tif_flags&TIFF_BIGTIFF))
		nextdir = tif->tif_header.classic.tiff_diroff;
	else
		nextdir = tif->tif_header.big.tiff_diroff;
	n = 0;
	while (nextdir != 0 && TIFFAdvanceDirectory(tif, &nextdir, NULL))
        {
                if (n != 65535) {
                        ++n;
                }
		else
                {
                        TIFFErrorExt(tif->tif_clientdata, module,
                                     "Directory count exceeded 65535 limit,"
                                     " giving up on counting.");
                        return (65535);
                }
        }
	return (n);
}