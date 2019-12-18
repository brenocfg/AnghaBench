#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  tmsize_t ;
struct TYPE_6__ {scalar_t__ td_nstrips; } ;
struct TYPE_7__ {TYPE_1__ tif_dir; int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ TIFFAppendToStrip (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  WRITECHECKTILES (TYPE_2__*,char const*) ; 

tmsize_t
TIFFWriteRawTile(TIFF* tif, uint32 tile, void* data, tmsize_t cc)
{
	static const char module[] = "TIFFWriteRawTile";

	if (!WRITECHECKTILES(tif, module))
		return ((tmsize_t)(-1));
	if (tile >= tif->tif_dir.td_nstrips) {
		TIFFErrorExt(tif->tif_clientdata, module, "Tile %lu out of range, max %lu",
		    (unsigned long) tile,
		    (unsigned long) tif->tif_dir.td_nstrips);
		return ((tmsize_t)(-1));
	}
	return (TIFFAppendToStrip(tif, tile, (uint8*) data, cc) ?
	    cc : (tmsize_t)(-1));
}