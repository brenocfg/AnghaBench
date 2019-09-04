#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint64 ;
typedef  size_t uint32 ;
typedef  scalar_t__ uint16 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_15__ {size_t td_nstrips; scalar_t__* td_stripbytecount; size_t td_tilelength; size_t td_tilewidth; scalar_t__ td_compression; size_t td_stripsperimage; int /*<<< orphan*/  td_fillorder; int /*<<< orphan*/  td_imagewidth; int /*<<< orphan*/  td_imagelength; } ;
struct TYPE_16__ {int tif_flags; size_t tif_curtile; scalar_t__ tif_rawdatasize; scalar_t__ tif_rawcc; size_t tif_row; size_t tif_col; scalar_t__ tif_tilesize; int /*<<< orphan*/ * tif_rawdata; int /*<<< orphan*/ * tif_rawcp; int /*<<< orphan*/  (* tif_postencode ) (TYPE_2__*) ;int /*<<< orphan*/  (* tif_encodetile ) (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* tif_postdecode ) (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ;int /*<<< orphan*/  (* tif_preencode ) (TYPE_2__*,scalar_t__) ;int /*<<< orphan*/  (* tif_setupencode ) (TYPE_2__*) ;int /*<<< orphan*/  tif_clientdata; scalar_t__ tif_curoff; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFERCHECK (TYPE_2__*) ; 
 scalar_t__ COMPRESSION_NONE ; 
 int /*<<< orphan*/  TIFFAppendToStrip (TYPE_2__*,size_t,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 int /*<<< orphan*/  TIFFReverseBits (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TIFFWriteBufferSetup (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int TIFF_BUF4WRITE ; 
 int TIFF_CODERSETUP ; 
 int TIFF_NOBITREV ; 
 int TIFF_POSTENCODE ; 
 size_t TIFFhowmany_32 (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ TIFFroundup_64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITECHECKTILES (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  isFillOrder (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*) ; 

tmsize_t
TIFFWriteEncodedTile(TIFF* tif, uint32 tile, void* data, tmsize_t cc)
{
	static const char module[] = "TIFFWriteEncodedTile";
	TIFFDirectory *td;
	uint16 sample;
        uint32 howmany32;

	if (!WRITECHECKTILES(tif, module))
		return ((tmsize_t)(-1));
	td = &tif->tif_dir;
	if (tile >= td->td_nstrips) {
		TIFFErrorExt(tif->tif_clientdata, module, "Tile %lu out of range, max %lu",
		    (unsigned long) tile, (unsigned long) td->td_nstrips);
		return ((tmsize_t)(-1));
	}
	/*
	 * Handle delayed allocation of data buffer.  This
	 * permits it to be sized more intelligently (using
	 * directory information).
	 */
	if (!BUFFERCHECK(tif))
		return ((tmsize_t)(-1));

        tif->tif_flags |= TIFF_BUF4WRITE;
	tif->tif_curtile = tile;

	if( td->td_stripbytecount[tile] > 0 )
        {
            /* Make sure that at the first attempt of rewriting the tile, we will have */
            /* more bytes available in the output buffer than the previous byte count, */
            /* so that TIFFAppendToStrip() will detect the overflow when it is called the first */
            /* time if the new compressed tile is bigger than the older one. (GDAL #4771) */
            if( tif->tif_rawdatasize <= (tmsize_t) td->td_stripbytecount[tile] )
            {
                if( !(TIFFWriteBufferSetup(tif, NULL,
                    (tmsize_t)TIFFroundup_64((uint64)(td->td_stripbytecount[tile] + 1), 1024))) )
                    return ((tmsize_t)(-1));
            }

	    /* Force TIFFAppendToStrip() to consider placing data at end
               of file. */
            tif->tif_curoff = 0;
        }

	tif->tif_rawcc = 0;
	tif->tif_rawcp = tif->tif_rawdata;

	/* 
	 * Compute tiles per row & per column to compute
	 * current row and column
	 */
        howmany32=TIFFhowmany_32(td->td_imagelength, td->td_tilelength);
        if (howmany32 == 0) {
                 TIFFErrorExt(tif->tif_clientdata,module,"Zero tiles");
                return ((tmsize_t)(-1));
        }
	tif->tif_row = (tile % howmany32) * td->td_tilelength;
        howmany32=TIFFhowmany_32(td->td_imagewidth, td->td_tilewidth);
        if (howmany32 == 0) {
                 TIFFErrorExt(tif->tif_clientdata,module,"Zero tiles");
                return ((tmsize_t)(-1));
        }
	tif->tif_col = (tile % howmany32) * td->td_tilewidth;

	if ((tif->tif_flags & TIFF_CODERSETUP) == 0) {
		if (!(*tif->tif_setupencode)(tif))
			return ((tmsize_t)(-1));
		tif->tif_flags |= TIFF_CODERSETUP;
	}
	tif->tif_flags &= ~TIFF_POSTENCODE;

	/*
	 * Clamp write amount to the tile size.  This is mostly
	 * done so that callers can pass in some large number
	 * (e.g. -1) and have the tile size used instead.
	 */
	if ( cc < 1 || cc > tif->tif_tilesize)
		cc = tif->tif_tilesize;

    /* shortcut to avoid an extra memcpy() */
    if( td->td_compression == COMPRESSION_NONE )
    {
        /* swab if needed - note that source buffer will be altered */
        tif->tif_postdecode( tif, (uint8*) data, cc );

        if (!isFillOrder(tif, td->td_fillorder) &&
            (tif->tif_flags & TIFF_NOBITREV) == 0)
            TIFFReverseBits((uint8*) data, cc);

        if (cc > 0 &&
            !TIFFAppendToStrip(tif, tile, (uint8*) data, cc))
            return ((tmsize_t) -1);
        return (cc);
    }

    sample = (uint16)(tile/td->td_stripsperimage);
    if (!(*tif->tif_preencode)(tif, sample))
        return ((tmsize_t)(-1));
    /* swab if needed - note that source buffer will be altered */
    tif->tif_postdecode( tif, (uint8*) data, cc );

    if (!(*tif->tif_encodetile)(tif, (uint8*) data, cc, sample))
            return ((tmsize_t) -1);
    if (!(*tif->tif_postencode)(tif))
            return ((tmsize_t)(-1));
    if (!isFillOrder(tif, td->td_fillorder) &&
        (tif->tif_flags & TIFF_NOBITREV) == 0)
            TIFFReverseBits((uint8*)tif->tif_rawdata, tif->tif_rawcc);
    if (tif->tif_rawcc > 0 && !TIFFAppendToStrip(tif, tile,
        tif->tif_rawdata, tif->tif_rawcc))
            return ((tmsize_t)(-1));
    tif->tif_rawcc = 0;
    tif->tif_rawcp = tif->tif_rawdata;
    return (cc);
}