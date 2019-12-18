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
typedef  scalar_t__ uint64 ;
typedef  size_t uint32 ;
typedef  scalar_t__ uint16 ;
typedef  int tmsize_t ;
struct TYPE_10__ {size_t td_imagelength; scalar_t__ td_planarconfig; scalar_t__ td_samplesperpixel; size_t td_stripsperimage; size_t td_rowsperstrip; scalar_t__* td_stripbytecount; scalar_t__ td_compression; } ;
struct TYPE_11__ {int tif_scanlinesize; size_t tif_curstrip; int tif_rawdata; int tif_rawdataloaded; int tif_rawcp; scalar_t__ tif_rawdataoff; size_t tif_row; int /*<<< orphan*/  (* tif_seek ) (TYPE_2__*,size_t) ;TYPE_1__ tif_dir; int /*<<< orphan*/  tif_name; int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ COMPRESSION_JBIG ; 
 scalar_t__ COMPRESSION_LERC ; 
 scalar_t__ PLANARCONFIG_SEPARATE ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  TIFFFillStrip (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  TIFFFillStripPartial (TYPE_2__*,size_t,int,int) ; 
 int /*<<< orphan*/  TIFFStartStrip (TYPE_2__*,size_t) ; 
 int TIFF_TMSIZE_T_MAX ; 
 int /*<<< orphan*/  _TIFFFillStriles (TYPE_2__*) ; 
 scalar_t__ isMapped (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t) ; 

__attribute__((used)) static int
TIFFSeek(TIFF* tif, uint32 row, uint16 sample )
{
	register TIFFDirectory *td = &tif->tif_dir;
	uint32 strip;
        int    whole_strip;
	tmsize_t read_ahead = 0;

        /*
        ** Establish what strip we are working from.
        */
	if (row >= td->td_imagelength) {	/* out of range */
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
		    "%lu: Row out of range, max %lu",
		    (unsigned long) row,
		    (unsigned long) td->td_imagelength);
		return (0);
	}
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE) {
		if (sample >= td->td_samplesperpixel) {
			TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			    "%lu: Sample out of range, max %lu",
			    (unsigned long) sample, (unsigned long) td->td_samplesperpixel);
			return (0);
		}
		strip = (uint32)sample*td->td_stripsperimage + row/td->td_rowsperstrip;
	} else
		strip = row / td->td_rowsperstrip;

        /*
         * Do we want to treat this strip as one whole chunk or
         * read it a few lines at a time?
         */
#if defined(CHUNKY_STRIP_READ_SUPPORT)
        if (!_TIFFFillStriles( tif ) || !tif->tif_dir.td_stripbytecount)
            return 0;
        whole_strip = tif->tif_dir.td_stripbytecount[strip] < 10
                || isMapped(tif);
        if( td->td_compression == COMPRESSION_LERC ||
            td->td_compression == COMPRESSION_JBIG )
        {
            /* Ideally plugins should have a way to declare they don't support
             * chunk strip */
            whole_strip = 1;
        }
#else
        whole_strip = 1;
#endif
        
        if( !whole_strip )
        {
                /* 16 is for YCbCr mode where we may need to read 16 */
                /* lines at a time to get a decompressed line, and 5000 */
                /* is some constant value, for example for JPEG tables */
                if( tif->tif_scanlinesize < TIFF_TMSIZE_T_MAX / 16 &&
                    tif->tif_scanlinesize * 16 < TIFF_TMSIZE_T_MAX - 5000 )
                {
                        read_ahead = tif->tif_scanlinesize * 16 + 5000;
                }
                else
                {
                        read_ahead = tif->tif_scanlinesize;
                }
        }

        /*
         * If we haven't loaded this strip, do so now, possibly
         * only reading the first part.
         */
	if (strip != tif->tif_curstrip) {	/* different strip, refill */
                
                if( whole_strip )
                {
                        if (!TIFFFillStrip(tif, strip))
                                return (0);
                }
                else
                {
                        if( !TIFFFillStripPartial(tif,strip,read_ahead,1) )
                                return 0;
                }
	}

        /*
        ** If we already have some data loaded, do we need to read some more?
        */
        else if( !whole_strip )
        {
                if( ((tif->tif_rawdata + tif->tif_rawdataloaded) - tif->tif_rawcp) < read_ahead 
                    && (uint64) tif->tif_rawdataoff+tif->tif_rawdataloaded < td->td_stripbytecount[strip] )
                {
                        if( !TIFFFillStripPartial(tif,strip,read_ahead,0) )
                                return 0;
                }
        }

        if (row < tif->tif_row) {
		/*
		 * Moving backwards within the same strip: backup
		 * to the start and then decode forward (below).
		 *
		 * NB: If you're planning on lots of random access within a
		 * strip, it's better to just read and decode the entire
		 * strip, and then access the decoded data in a random fashion.
		 */

                if( tif->tif_rawdataoff != 0 )
                {
                        if( !TIFFFillStripPartial(tif,strip,read_ahead,1) )
                                return 0;
                }
                else
                {
                        if (!TIFFStartStrip(tif, strip))
                                return (0);
                }
	}
        
	if (row != tif->tif_row) {
		/*
		 * Seek forward to the desired row.
		 */

                /* TODO: Will this really work with partial buffers? */
                
		if (!(*tif->tif_seek)(tif, row - tif->tif_row))
			return (0);
		tif->tif_row = row;
	}

	return (1);
}