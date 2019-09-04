#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  size_t uint32 ;
typedef  scalar_t__ tmsize_t ;
typedef  scalar_t__ int64 ;
struct TYPE_12__ {int* td_stripbytecount; int* td_stripoffset; int /*<<< orphan*/  td_fillorder; } ;
struct TYPE_13__ {int tif_flags; scalar_t__ tif_rawdatasize; scalar_t__ tif_base; scalar_t__ tif_rawdataloaded; int /*<<< orphan*/ * tif_rawdata; scalar_t__ tif_rawdataoff; void* tif_curtile; int /*<<< orphan*/  tif_clientdata; scalar_t__ tif_size; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 void* NOTILE ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 int /*<<< orphan*/  TIFFReadBufferSetup (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TIFFReadRawStripOrTile2 (TYPE_2__*,size_t,int /*<<< orphan*/ ,scalar_t__,char const*) ; 
 scalar_t__ TIFFReadRawTile1 (TYPE_2__*,size_t,int /*<<< orphan*/ *,scalar_t__,char const*) ; 
 int /*<<< orphan*/  TIFFReverseBits (int /*<<< orphan*/ *,scalar_t__) ; 
 int TIFFStartTile (TYPE_2__*,size_t) ; 
 scalar_t__ TIFFTileSize (TYPE_2__*) ; 
 int TIFF_BUFFERMMAP ; 
 int TIFF_MYBUFFER ; 
 int TIFF_NOBITREV ; 
 int TIFF_NOREADRAW ; 
 int /*<<< orphan*/  _TIFFFillStriles (TYPE_2__*) ; 
 int /*<<< orphan*/  _TIFFfree (int /*<<< orphan*/ *) ; 
 scalar_t__ isFillOrder (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ isMapped (TYPE_2__*) ; 

int
TIFFFillTile(TIFF* tif, uint32 tile)
{
	static const char module[] = "TIFFFillTile";
	TIFFDirectory *td = &tif->tif_dir;

        if (!_TIFFFillStriles( tif ) || !tif->tif_dir.td_stripbytecount)
            return 0;

	if ((tif->tif_flags&TIFF_NOREADRAW)==0)
	{
		uint64 bytecount = td->td_stripbytecount[tile];
		if ((int64)bytecount <= 0) {
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
			TIFFErrorExt(tif->tif_clientdata, module,
				"%I64u: Invalid tile byte count, tile %lu",
				     (unsigned __int64) bytecount,
				     (unsigned long) tile);
#else
			TIFFErrorExt(tif->tif_clientdata, module,
				"%llu: Invalid tile byte count, tile %lu",
				     (unsigned long long) bytecount,
				     (unsigned long) tile);
#endif
			return (0);
		}

		/* To avoid excessive memory allocations: */
		/* Byte count should normally not be larger than a number of */
		/* times the uncompressed size plus some margin */
                if( bytecount > 1024 * 1024 )
                {
			/* 10 and 4096 are just values that could be adjusted. */
			/* Hopefully they are safe enough for all codecs */
			tmsize_t stripsize = TIFFTileSize(tif);
			if( stripsize != 0 &&
			    (bytecount - 4096) / 10 > (uint64)stripsize  )
			{
				uint64 newbytecount = (uint64)stripsize * 10 + 4096;
				if( (int64)newbytecount >= 0 )
				{
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
					TIFFWarningExt(tif->tif_clientdata, module,
					  "Too large tile byte count %I64u, tile %lu. Limiting to %I64u",
					     (unsigned __int64) bytecount,
					     (unsigned long) tile,
					     (unsigned __int64) newbytecount);
#else
					TIFFErrorExt(tif->tif_clientdata, module,
					  "Too large tile byte count %llu, tile %lu. Limiting to %llu",
					     (unsigned long long) bytecount,
					     (unsigned long) tile,
					     (unsigned long long) newbytecount);
#endif
					bytecount = newbytecount;
				}
			}
		}

		if (isMapped(tif)) {
			/*
			 * We must check for overflow, potentially causing
			 * an OOB read. Instead of simple
			 *
			 *  td->td_stripoffset[tile]+bytecount > tif->tif_size
			 *
			 * comparison (which can overflow) we do the following
			 * two comparisons:
			 */
			if (bytecount > (uint64)tif->tif_size ||
			    td->td_stripoffset[tile] > (uint64)tif->tif_size - bytecount) {
				tif->tif_curtile = NOTILE;
				return (0);
			}
		}

		if (isMapped(tif) &&
		    (isFillOrder(tif, td->td_fillorder)
		     || (tif->tif_flags & TIFF_NOBITREV))) {
			/*
			 * The image is mapped into memory and we either don't
			 * need to flip bits or the compression routine is
			 * going to handle this operation itself.  In this
			 * case, avoid copying the raw data and instead just
			 * reference the data from the memory mapped file
			 * image.  This assumes that the decompression
			 * routines do not modify the contents of the raw data
			 * buffer (if they try to, the application will get a
			 * fault since the file is mapped read-only).
			 */
			if ((tif->tif_flags & TIFF_MYBUFFER) && tif->tif_rawdata) {
				_TIFFfree(tif->tif_rawdata);
				tif->tif_rawdata = NULL;
				tif->tif_rawdatasize = 0;
			}
			tif->tif_flags &= ~TIFF_MYBUFFER;

			tif->tif_rawdatasize = (tmsize_t)bytecount;
			tif->tif_rawdata =
				tif->tif_base + (tmsize_t)td->td_stripoffset[tile];
                        tif->tif_rawdataoff = 0;
                        tif->tif_rawdataloaded = (tmsize_t) bytecount;
			tif->tif_flags |= TIFF_BUFFERMMAP;
		} else {
			/*
			 * Expand raw data buffer, if needed, to hold data
			 * tile coming from file (perhaps should set upper
			 * bound on the size of a buffer we'll use?).
			 */
			tmsize_t bytecountm;
			bytecountm=(tmsize_t)bytecount;
			if ((uint64)bytecountm!=bytecount)
			{
				TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
				return(0);
			}
			if (bytecountm > tif->tif_rawdatasize) {
				tif->tif_curtile = NOTILE;
				if ((tif->tif_flags & TIFF_MYBUFFER) == 0) {
					TIFFErrorExt(tif->tif_clientdata, module,
					    "Data buffer too small to hold tile %lu",
					    (unsigned long) tile);
					return (0);
				}
			}
			if (tif->tif_flags&TIFF_BUFFERMMAP) {
				tif->tif_curtile = NOTILE;
				tif->tif_rawdata = NULL;
				tif->tif_rawdatasize = 0;
				tif->tif_flags &= ~TIFF_BUFFERMMAP;
			}

			if( isMapped(tif) )
			{
				if (bytecountm > tif->tif_rawdatasize &&
				    !TIFFReadBufferSetup(tif, 0, bytecountm))
				{
					return (0);
				}
				if (TIFFReadRawTile1(tif, tile, tif->tif_rawdata,
				    bytecountm, module) != bytecountm)
				{
					return (0);
				}
			}
			else
			{
				if (TIFFReadRawStripOrTile2(tif, tile, 0,
				    bytecountm, module) != bytecountm)
				{
					return (0);
				}
			}


                        tif->tif_rawdataoff = 0;
                        tif->tif_rawdataloaded = bytecountm;
                        
			if (!isFillOrder(tif, td->td_fillorder) &&
			    (tif->tif_flags & TIFF_NOBITREV) == 0)
				TIFFReverseBits(tif->tif_rawdata,
                                                tif->tif_rawdataloaded);
		}
	}
	return (TIFFStartTile(tif, tile));
}