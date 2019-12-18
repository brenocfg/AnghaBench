#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_14__ {struct TYPE_14__* fields; scalar_t__ allocated_size; } ;
struct TYPE_11__ {int /*<<< orphan*/ * printdir; int /*<<< orphan*/  vgetfield; int /*<<< orphan*/  vsetfield; } ;
struct TYPE_12__ {int td_bitspersample; int td_samplesperpixel; size_t td_rowsperstrip; int td_tiledepth; int td_stripbytecountsorted; int td_imagedepth; int* td_ycbcrsubsampling; int /*<<< orphan*/  td_ycbcrpositioning; int /*<<< orphan*/  td_sampleformat; int /*<<< orphan*/  td_resolutionunit; scalar_t__ td_tilelength; scalar_t__ td_tilewidth; int /*<<< orphan*/  td_orientation; int /*<<< orphan*/  td_threshholding; int /*<<< orphan*/  td_fillorder; } ;
struct TYPE_13__ {scalar_t__ tif_nfieldscompat; int /*<<< orphan*/  tif_flags; TYPE_6__* tif_fieldscompat; TYPE_1__ tif_tagmethods; int /*<<< orphan*/ * tif_foundfield; int /*<<< orphan*/  tif_postdecode; TYPE_2__ tif_dir; } ;
typedef  int /*<<< orphan*/  TIFFFieldArray ;
typedef  TYPE_2__ TIFFDirectory ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  COMPRESSION_NONE ; 
 int /*<<< orphan*/  FILLORDER_MSB2LSB ; 
 int /*<<< orphan*/  ORIENTATION_TOPLEFT ; 
 int /*<<< orphan*/  RESUNIT_INCH ; 
 int /*<<< orphan*/  SAMPLEFORMAT_UINT ; 
 int /*<<< orphan*/  THRESHHOLD_BILEVEL ; 
 int /*<<< orphan*/  TIFFSetField (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFTAG_COMPRESSION ; 
 int /*<<< orphan*/  TIFF_DIRTYDIRECT ; 
 int /*<<< orphan*/  TIFF_ISTILED ; 
 int /*<<< orphan*/  YCBCRPOSITION_CENTERED ; 
 int /*<<< orphan*/ * _TIFFGetFields () ; 
 int /*<<< orphan*/  _TIFFNoPostDecode ; 
 int /*<<< orphan*/  _TIFFSetupFields (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _TIFFVGetField ; 
 int /*<<< orphan*/  _TIFFVSetField ; 
 int /*<<< orphan*/  _TIFFextender (TYPE_3__*) ; 
 int /*<<< orphan*/  _TIFFfree (TYPE_6__*) ; 
 int /*<<< orphan*/  _TIFFmemset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

int
TIFFDefaultDirectory(TIFF* tif)
{
	register TIFFDirectory* td = &tif->tif_dir;
	const TIFFFieldArray* tiffFieldArray;

	tiffFieldArray = _TIFFGetFields();
	_TIFFSetupFields(tif, tiffFieldArray);   

	_TIFFmemset(td, 0, sizeof (*td));
	td->td_fillorder = FILLORDER_MSB2LSB;
	td->td_bitspersample = 1;
	td->td_threshholding = THRESHHOLD_BILEVEL;
	td->td_orientation = ORIENTATION_TOPLEFT;
	td->td_samplesperpixel = 1;
	td->td_rowsperstrip = (uint32) -1;
	td->td_tilewidth = 0;
	td->td_tilelength = 0;
	td->td_tiledepth = 1;
	td->td_stripbytecountsorted = 1; /* Our own arrays always sorted. */  
	td->td_resolutionunit = RESUNIT_INCH;
	td->td_sampleformat = SAMPLEFORMAT_UINT;
	td->td_imagedepth = 1;
	td->td_ycbcrsubsampling[0] = 2;
	td->td_ycbcrsubsampling[1] = 2;
	td->td_ycbcrpositioning = YCBCRPOSITION_CENTERED;
	tif->tif_postdecode = _TIFFNoPostDecode;  
	tif->tif_foundfield = NULL;
	tif->tif_tagmethods.vsetfield = _TIFFVSetField;  
	tif->tif_tagmethods.vgetfield = _TIFFVGetField;
	tif->tif_tagmethods.printdir = NULL;
	/*
	 *  Give client code a chance to install their own
	 *  tag extensions & methods, prior to compression overloads,
	 *  but do some prior cleanup first. (http://trac.osgeo.org/gdal/ticket/5054)
	 */
	if (tif->tif_nfieldscompat > 0) {
		uint32 i;

		for (i = 0; i < tif->tif_nfieldscompat; i++) {
				if (tif->tif_fieldscompat[i].allocated_size)
						_TIFFfree(tif->tif_fieldscompat[i].fields);
		}
		_TIFFfree(tif->tif_fieldscompat);
		tif->tif_nfieldscompat = 0;
		tif->tif_fieldscompat = NULL;
	}
	if (_TIFFextender)
		(*_TIFFextender)(tif);
	(void) TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
	/*
	 * NB: The directory is marked dirty as a result of setting
	 * up the default compression scheme.  However, this really
	 * isn't correct -- we want TIFF_DIRTYDIRECT to be set only
	 * if the user does something.  We could just do the setup
	 * by hand, but it seems better to use the normal mechanism
	 * (i.e. TIFFSetField).
	 */
	tif->tif_flags &= ~TIFF_DIRTYDIRECT;

	/*
	 * As per http://bugzilla.remotesensing.org/show_bug.cgi?id=19
	 * we clear the ISTILED flag when setting up a new directory.
	 * Should we also be clearing stuff like INSUBIFD?
	 */
	tif->tif_flags &= ~TIFF_ISTILED;

	return (1);
}