#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  int uint32 ;
struct TYPE_9__ {int* td_stripbytecount; int* td_stripoffset; scalar_t__ td_planarconfig; scalar_t__ td_photometric; int* td_ycbcrsubsampling; int td_rowsperstrip; int td_stripsperimage; int td_nstrips; int td_stripbytecountsorted; int /*<<< orphan*/  td_imagelength; } ;
struct TYPE_10__ {scalar_t__ tif_mode; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ O_RDONLY ; 
 scalar_t__ PHOTOMETRIC_YCBCR ; 
 scalar_t__ PLANARCONFIG_CONTIG ; 
 int STRIP_SIZE_DEFAULT ; 
 int TIFFGetFileSize (TYPE_2__*) ; 
 int /*<<< orphan*/  TIFFSetField (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TIFFTAG_ROWSPERSTRIP ; 
 int TIFFVTileSize64 (TYPE_2__*,int) ; 
 int TIFFhowmany_32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ _TIFFCheckMalloc (TYPE_2__*,int,int,char*) ; 
 int /*<<< orphan*/  _TIFFfree (int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  isUpSampled (TYPE_2__*) ; 

__attribute__((used)) static void
ChopUpSingleUncompressedStrip(TIFF* tif)
{
	register TIFFDirectory *td = &tif->tif_dir;
	uint64 bytecount;
	uint64 offset;
	uint32 rowblock;
	uint64 rowblockbytes;
	uint64 stripbytes;
	uint32 strip;
	uint32 nstrips;
	uint32 rowsperstrip;
	uint64* newcounts;
	uint64* newoffsets;

	bytecount = td->td_stripbytecount[0];
        /* On a newly created file, just re-opened to be filled, we */
        /* don't want strip chop to trigger as it is going to cause issues */
        /* later ( StripOffsets and StripByteCounts improperly filled) . */
        if( bytecount == 0 && tif->tif_mode != O_RDONLY )
            return;
	offset = td->td_stripoffset[0];
	assert(td->td_planarconfig == PLANARCONFIG_CONTIG);
	if ((td->td_photometric == PHOTOMETRIC_YCBCR)&&
	    (!isUpSampled(tif)))
		rowblock = td->td_ycbcrsubsampling[1];
	else
		rowblock = 1;
	rowblockbytes = TIFFVTileSize64(tif, rowblock);
	/*
	 * Make the rows hold at least one scanline, but fill specified amount
	 * of data if possible.
	 */
	if (rowblockbytes > STRIP_SIZE_DEFAULT) {
		stripbytes = rowblockbytes;
		rowsperstrip = rowblock;
	} else if (rowblockbytes > 0 ) {
		uint32 rowblocksperstrip;
		rowblocksperstrip = (uint32) (STRIP_SIZE_DEFAULT / rowblockbytes);
		rowsperstrip = rowblocksperstrip * rowblock;
		stripbytes = rowblocksperstrip * rowblockbytes;
	}
	else
	    return;

	/*
	 * never increase the number of rows per strip
	 */
	if (rowsperstrip >= td->td_rowsperstrip)
		return;
        nstrips = TIFFhowmany_32(td->td_imagelength, rowsperstrip);
        if( nstrips == 0 )
            return;

        /* If we are going to allocate a lot of memory, make sure that the */
        /* file is as big as needed */
        if( tif->tif_mode == O_RDONLY &&
            nstrips > 1000000 &&
            (offset >= TIFFGetFileSize(tif) ||
             stripbytes > (TIFFGetFileSize(tif) - offset) / (nstrips - 1)) )
        {
            return;
        }

	newcounts = (uint64*) _TIFFCheckMalloc(tif, nstrips, sizeof (uint64),
				"for chopped \"StripByteCounts\" array");
	newoffsets = (uint64*) _TIFFCheckMalloc(tif, nstrips, sizeof (uint64),
				"for chopped \"StripOffsets\" array");
	if (newcounts == NULL || newoffsets == NULL) {
		/*
		 * Unable to allocate new strip information, give up and use
		 * the original one strip information.
		 */
		if (newcounts != NULL)
			_TIFFfree(newcounts);
		if (newoffsets != NULL)
			_TIFFfree(newoffsets);
		return;
	}
	/*
	 * Fill the strip information arrays with new bytecounts and offsets
	 * that reflect the broken-up format.
	 */
	for (strip = 0; strip < nstrips; strip++) {
		if (stripbytes > bytecount)
			stripbytes = bytecount;
		newcounts[strip] = stripbytes;
		newoffsets[strip] = stripbytes ? offset : 0;
		offset += stripbytes;
		bytecount -= stripbytes;
	}
	/*
	 * Replace old single strip info with multi-strip info.
	 */
	td->td_stripsperimage = td->td_nstrips = nstrips;
	TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, rowsperstrip);

	_TIFFfree(td->td_stripbytecount);
	_TIFFfree(td->td_stripoffset);
	td->td_stripbytecount = newcounts;
	td->td_stripoffset = newoffsets;
	td->td_stripbytecountsorted = 1;
}