#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
typedef  int uint16 ;
struct TYPE_13__ {int td_imagelength; scalar_t__ td_planarconfig; int td_samplesperpixel; int td_stripsperimage; int td_rowsperstrip; int td_nstrips; scalar_t__* td_stripbytecount; } ;
struct TYPE_14__ {int tif_flags; int tif_curstrip; int tif_row; int (* tif_encoderow ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  tif_scanlinesize; int /*<<< orphan*/  (* tif_postdecode ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* tif_seek ) (TYPE_2__*,int) ;int /*<<< orphan*/  tif_rawdata; int /*<<< orphan*/  tif_rawcp; int /*<<< orphan*/  (* tif_preencode ) (TYPE_2__*,int) ;scalar_t__ tif_curoff; scalar_t__ tif_rawcc; int /*<<< orphan*/  (* tif_setupencode ) (TYPE_2__*) ;int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFERCHECK (TYPE_2__*) ; 
 scalar_t__ PLANARCONFIG_SEPARATE ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 int /*<<< orphan*/  TIFFFlushData (TYPE_2__*) ; 
 int /*<<< orphan*/  TIFFGrowStrips (TYPE_2__*,int,char const*) ; 
 int TIFF_BUF4WRITE ; 
 int TIFF_CODERSETUP ; 
 int TIFF_POSTENCODE ; 
 int TIFFhowmany_32 (int,int) ; 
 int /*<<< orphan*/  WRITECHECKSTRIPS (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub5 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
TIFFWriteScanline(TIFF* tif, void* buf, uint32 row, uint16 sample)
{
	static const char module[] = "TIFFWriteScanline";
	register TIFFDirectory *td;
	int status, imagegrew = 0;
	uint32 strip;

	if (!WRITECHECKSTRIPS(tif, module))
		return (-1);
	/*
	 * Handle delayed allocation of data buffer.  This
	 * permits it to be sized more intelligently (using
	 * directory information).
	 */
	if (!BUFFERCHECK(tif))
		return (-1);
        tif->tif_flags |= TIFF_BUF4WRITE; /* not strictly sure this is right*/

	td = &tif->tif_dir;
	/*
	 * Extend image length if needed
	 * (but only for PlanarConfig=1).
	 */
	if (row >= td->td_imagelength) {	/* extend image */
		if (td->td_planarconfig == PLANARCONFIG_SEPARATE) {
			TIFFErrorExt(tif->tif_clientdata, module,
			    "Can not change \"ImageLength\" when using separate planes");
			return (-1);
		}
		td->td_imagelength = row+1;
		imagegrew = 1;
	}
	/*
	 * Calculate strip and check for crossings.
	 */
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE) {
		if (sample >= td->td_samplesperpixel) {
			TIFFErrorExt(tif->tif_clientdata, module,
			    "%lu: Sample out of range, max %lu",
			    (unsigned long) sample, (unsigned long) td->td_samplesperpixel);
			return (-1);
		}
		strip = sample*td->td_stripsperimage + row/td->td_rowsperstrip;
	} else
		strip = row / td->td_rowsperstrip;
	/*
	 * Check strip array to make sure there's space. We don't support
	 * dynamically growing files that have data organized in separate
	 * bitplanes because it's too painful.  In that case we require that
	 * the imagelength be set properly before the first write (so that the
	 * strips array will be fully allocated above).
	 */
	if (strip >= td->td_nstrips && !TIFFGrowStrips(tif, 1, module))
		return (-1);
	if (strip != tif->tif_curstrip) {
		/*
		 * Changing strips -- flush any data present.
		 */
		if (!TIFFFlushData(tif))
			return (-1);
		tif->tif_curstrip = strip;
		/*
		 * Watch out for a growing image.  The value of strips/image
		 * will initially be 1 (since it can't be deduced until the
		 * imagelength is known).
		 */
		if (strip >= td->td_stripsperimage && imagegrew)
			td->td_stripsperimage =
			    TIFFhowmany_32(td->td_imagelength,td->td_rowsperstrip);
                if (td->td_stripsperimage == 0) {
                        TIFFErrorExt(tif->tif_clientdata, module, "Zero strips per image");
                        return (-1);
                }
		tif->tif_row =
		    (strip % td->td_stripsperimage) * td->td_rowsperstrip;
		if ((tif->tif_flags & TIFF_CODERSETUP) == 0) {
			if (!(*tif->tif_setupencode)(tif))
				return (-1);
			tif->tif_flags |= TIFF_CODERSETUP;
		}
        
		tif->tif_rawcc = 0;
		tif->tif_rawcp = tif->tif_rawdata;

		if( td->td_stripbytecount[strip] > 0 )
		{
			/* if we are writing over existing tiles, zero length */
			td->td_stripbytecount[strip] = 0;

			/* this forces TIFFAppendToStrip() to do a seek */
			tif->tif_curoff = 0;
		}

		if (!(*tif->tif_preencode)(tif, sample))
			return (-1);
		tif->tif_flags |= TIFF_POSTENCODE;
	}
	/*
	 * Ensure the write is either sequential or at the
	 * beginning of a strip (or that we can randomly
	 * access the data -- i.e. no encoding).
	 */
	if (row != tif->tif_row) {
		if (row < tif->tif_row) {
			/*
			 * Moving backwards within the same strip:
			 * backup to the start and then decode
			 * forward (below).
			 */
			tif->tif_row = (strip % td->td_stripsperimage) *
			    td->td_rowsperstrip;
			tif->tif_rawcp = tif->tif_rawdata;
		}
		/*
		 * Seek forward to the desired row.
		 */
		if (!(*tif->tif_seek)(tif, row - tif->tif_row))
			return (-1);
		tif->tif_row = row;
	}

	/* swab if needed - note that source buffer will be altered */
	tif->tif_postdecode( tif, (uint8*) buf, tif->tif_scanlinesize );

	status = (*tif->tif_encoderow)(tif, (uint8*) buf,
	    tif->tif_scanlinesize, sample);

        /* we are now poised at the beginning of the next row */
	tif->tif_row = row + 1;
	return (status);
}