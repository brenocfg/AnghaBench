#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_10__ {scalar_t__ td_nstrips; scalar_t__ td_stripsperimage; } ;
struct TYPE_11__ {scalar_t__ tif_tilesize; int /*<<< orphan*/  (* tif_postdecode ) (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ;scalar_t__ (* tif_decodetile ) (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFCheckRead (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 int /*<<< orphan*/  TIFFFileName (TYPE_2__*) ; 
 int /*<<< orphan*/  TIFFFillTile (TYPE_2__*,scalar_t__) ; 
 scalar_t__ TIFFReadEncodedTile (TYPE_2__*,scalar_t__,void*,scalar_t__) ; 
 void* _TIFFmalloc (scalar_t__) ; 
 int /*<<< orphan*/  _TIFFmemset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 

tmsize_t
_TIFFReadEncodedTileAndAllocBuffer(TIFF* tif, uint32 tile,
                                    void **buf, tmsize_t bufsizetoalloc,
                                    tmsize_t size_to_read)
{
    static const char module[] = "_TIFFReadEncodedTileAndAllocBuffer";
    TIFFDirectory *td = &tif->tif_dir;
    tmsize_t tilesize = tif->tif_tilesize;

    if( *buf != NULL )
    {
        return TIFFReadEncodedTile(tif, tile, *buf, size_to_read);
    }

    if (!TIFFCheckRead(tif, 1))
            return ((tmsize_t)(-1));
    if (tile >= td->td_nstrips) {
            TIFFErrorExt(tif->tif_clientdata, module,
                "%lu: Tile out of range, max %lu",
                (unsigned long) tile, (unsigned long) td->td_nstrips);
            return ((tmsize_t)(-1));
    }

    if (!TIFFFillTile(tif,tile))
            return((tmsize_t)(-1));

    *buf = _TIFFmalloc(bufsizetoalloc);
    if (*buf == NULL) {
            TIFFErrorExt(tif->tif_clientdata, TIFFFileName(tif),
                         "No space for tile buffer");
            return((tmsize_t)(-1));
    }
    _TIFFmemset(*buf, 0, bufsizetoalloc);

    if (size_to_read == (tmsize_t)(-1))
        size_to_read = tilesize;
    else if (size_to_read > tilesize)
        size_to_read = tilesize;
    if( (*tif->tif_decodetile)(tif,
        (uint8*) *buf, size_to_read, (uint16)(tile/td->td_stripsperimage))) {
        (*tif->tif_postdecode)(tif, (uint8*) *buf, size_to_read);
        return (size_to_read);
    } else
        return ((tmsize_t)(-1));
}