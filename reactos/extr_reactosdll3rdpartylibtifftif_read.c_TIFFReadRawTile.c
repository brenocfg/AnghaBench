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
typedef  scalar_t__ uint64 ;
typedef  size_t uint32 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_6__ {size_t td_nstrips; scalar_t__* td_stripbytecount; } ;
struct TYPE_7__ {int tif_flags; int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFCheckRead (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 scalar_t__ TIFFReadRawTile1 (TYPE_2__*,size_t,void*,scalar_t__,char const*) ; 
 int TIFF_NOREADRAW ; 

tmsize_t
TIFFReadRawTile(TIFF* tif, uint32 tile, void* buf, tmsize_t size)
{
	static const char module[] = "TIFFReadRawTile";
	TIFFDirectory *td = &tif->tif_dir;
	uint64 bytecount64;
	tmsize_t bytecountm;

	if (!TIFFCheckRead(tif, 1))
		return ((tmsize_t)(-1));
	if (tile >= td->td_nstrips) {
		TIFFErrorExt(tif->tif_clientdata, module,
		    "%lu: Tile out of range, max %lu",
		    (unsigned long) tile, (unsigned long) td->td_nstrips);
		return ((tmsize_t)(-1));
	}
	if (tif->tif_flags&TIFF_NOREADRAW)
	{
		TIFFErrorExt(tif->tif_clientdata, module,
		"Compression scheme does not support access to raw uncompressed data");
		return ((tmsize_t)(-1));
	}
	bytecount64 = td->td_stripbytecount[tile];
	if (size != (tmsize_t)(-1) && (uint64)size < bytecount64)
		bytecount64 = (uint64)size;
	bytecountm = (tmsize_t)bytecount64;
	if ((uint64)bytecountm!=bytecount64)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
		return ((tmsize_t)(-1));
	}
	return (TIFFReadRawTile1(tif, tile, buf, bytecountm, module));
}