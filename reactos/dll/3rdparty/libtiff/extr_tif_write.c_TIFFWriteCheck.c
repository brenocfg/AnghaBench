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
typedef  scalar_t__ tmsize_t ;
struct TYPE_10__ {int td_samplesperpixel; scalar_t__ td_nstrips; int /*<<< orphan*/ * td_stripoffset; int /*<<< orphan*/  td_planarconfig; } ;
struct TYPE_11__ {scalar_t__ tif_mode; scalar_t__ tif_tilesize; scalar_t__ tif_scanlinesize; int /*<<< orphan*/  tif_flags; int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_IMAGEDIMENSIONS ; 
 int /*<<< orphan*/  FIELD_PLANARCONFIG ; 
 scalar_t__ O_RDONLY ; 
 int /*<<< orphan*/  PLANARCONFIG_CONTIG ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 int /*<<< orphan*/  TIFFFieldSet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TIFFScanlineSize (TYPE_2__*) ; 
 int /*<<< orphan*/  TIFFSetupStrips (TYPE_2__*) ; 
 scalar_t__ TIFFTileSize (TYPE_2__*) ; 
 int /*<<< orphan*/  TIFF_BEENWRITING ; 
 int /*<<< orphan*/  _TIFFFillStriles (TYPE_2__*) ; 
 int isTiled (TYPE_2__*) ; 

int
TIFFWriteCheck(TIFF* tif, int tiles, const char* module)
{
	if (tif->tif_mode == O_RDONLY) {
		TIFFErrorExt(tif->tif_clientdata, module, "File not open for writing");
		return (0);
	}
	if (tiles ^ isTiled(tif)) {
		TIFFErrorExt(tif->tif_clientdata, module, tiles ?
		    "Can not write tiles to a stripped image" :
		    "Can not write scanlines to a tiled image");
		return (0);
	}

        _TIFFFillStriles( tif );
        
	/*
	 * On the first write verify all the required information
	 * has been setup and initialize any data structures that
	 * had to wait until directory information was set.
	 * Note that a lot of our work is assumed to remain valid
	 * because we disallow any of the important parameters
	 * from changing after we start writing (i.e. once
	 * TIFF_BEENWRITING is set, TIFFSetField will only allow
	 * the image's length to be changed).
	 */
	if (!TIFFFieldSet(tif, FIELD_IMAGEDIMENSIONS)) {
		TIFFErrorExt(tif->tif_clientdata, module,
		    "Must set \"ImageWidth\" before writing data");
		return (0);
	}
	if (tif->tif_dir.td_samplesperpixel == 1) {
		/* 
		 * Planarconfiguration is irrelevant in case of single band
		 * images and need not be included. We will set it anyway,
		 * because this field is used in other parts of library even
		 * in the single band case.
		 */
		if (!TIFFFieldSet(tif, FIELD_PLANARCONFIG))
                    tif->tif_dir.td_planarconfig = PLANARCONFIG_CONTIG;
	} else {
		if (!TIFFFieldSet(tif, FIELD_PLANARCONFIG)) {
			TIFFErrorExt(tif->tif_clientdata, module,
			    "Must set \"PlanarConfiguration\" before writing data");
			return (0);
		}
	}
	if (tif->tif_dir.td_stripoffset == NULL && !TIFFSetupStrips(tif)) {
		tif->tif_dir.td_nstrips = 0;
		TIFFErrorExt(tif->tif_clientdata, module, "No space for %s arrays",
		    isTiled(tif) ? "tile" : "strip");
		return (0);
	}
	if (isTiled(tif))
	{
		tif->tif_tilesize = TIFFTileSize(tif);
		if (tif->tif_tilesize == 0)
			return (0);
	}
	else
		tif->tif_tilesize = (tmsize_t)(-1);
	tif->tif_scanlinesize = TIFFScanlineSize(tif);
	if (tif->tif_scanlinesize == 0)
		return (0);
	tif->tif_flags |= TIFF_BEENWRITING;
	return (1);
}