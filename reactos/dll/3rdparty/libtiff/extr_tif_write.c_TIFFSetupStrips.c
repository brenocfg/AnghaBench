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
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_10__ {int td_stripsperimage; int td_samplesperpixel; int td_nstrips; scalar_t__ td_planarconfig; int /*<<< orphan*/ * td_stripbytecount; int /*<<< orphan*/ * td_stripoffset; } ;
struct TYPE_11__ {TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_ROWSPERSTRIP ; 
 int /*<<< orphan*/  FIELD_STRIPBYTECOUNTS ; 
 int /*<<< orphan*/  FIELD_STRIPOFFSETS ; 
 int /*<<< orphan*/  FIELD_TILEDIMENSIONS ; 
 scalar_t__ PLANARCONFIG_SEPARATE ; 
 int TIFFNumberOfStrips (TYPE_2__*) ; 
 int TIFFNumberOfTiles (TYPE_2__*) ; 
 int /*<<< orphan*/  TIFFSetFieldBit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _TIFFCheckMalloc (TYPE_2__*,int,int,char*) ; 
 int /*<<< orphan*/  _TIFFmemset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ isTiled (TYPE_2__*) ; 
 scalar_t__ isUnspecified (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
TIFFSetupStrips(TIFF* tif)
{
	TIFFDirectory* td = &tif->tif_dir;

	if (isTiled(tif))
		td->td_stripsperimage =
		    isUnspecified(tif, FIELD_TILEDIMENSIONS) ?
			td->td_samplesperpixel : TIFFNumberOfTiles(tif);
	else
		td->td_stripsperimage =
		    isUnspecified(tif, FIELD_ROWSPERSTRIP) ?
			td->td_samplesperpixel : TIFFNumberOfStrips(tif);
	td->td_nstrips = td->td_stripsperimage;
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE)
		td->td_stripsperimage /= td->td_samplesperpixel;
	td->td_stripoffset = (uint64 *)
            _TIFFCheckMalloc(tif, td->td_nstrips, sizeof (uint64),
                             "for \"StripOffsets\" array");
	td->td_stripbytecount = (uint64 *)
            _TIFFCheckMalloc(tif, td->td_nstrips, sizeof (uint64),
                             "for \"StripByteCounts\" array");
	if (td->td_stripoffset == NULL || td->td_stripbytecount == NULL)
		return (0);
	/*
	 * Place data at the end-of-file
	 * (by setting offsets to zero).
	 */
	_TIFFmemset(td->td_stripoffset, 0, td->td_nstrips*sizeof (uint64));
	_TIFFmemset(td->td_stripbytecount, 0, td->td_nstrips*sizeof (uint64));
	TIFFSetFieldBit(tif, FIELD_STRIPOFFSETS);
	TIFFSetFieldBit(tif, FIELD_STRIPBYTECOUNTS);
	return (1);
}