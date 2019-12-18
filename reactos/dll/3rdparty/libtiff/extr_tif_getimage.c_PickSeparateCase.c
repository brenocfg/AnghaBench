#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_7__ {int /*<<< orphan*/ * separate; } ;
struct TYPE_8__ {int photometric; int bitspersample; int alpha; int samplesperpixel; TYPE_1__ put; int /*<<< orphan*/ * get; int /*<<< orphan*/  tif; } ;
typedef  TYPE_2__ TIFFRGBAImage ;

/* Variables and functions */
 int /*<<< orphan*/  BuildMapBitdepth16To8 (TYPE_2__*) ; 
 int /*<<< orphan*/  BuildMapUaToAa (TYPE_2__*) ; 
 int EXTRASAMPLE_ASSOCALPHA ; 
 int EXTRASAMPLE_UNASSALPHA ; 
#define  PHOTOMETRIC_MINISBLACK 132 
#define  PHOTOMETRIC_MINISWHITE 131 
#define  PHOTOMETRIC_RGB 130 
#define  PHOTOMETRIC_SEPARATED 129 
#define  PHOTOMETRIC_YCBCR 128 
 int /*<<< orphan*/  TIFFGetFieldDefaulted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ TIFFIsTiled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFTAG_YCBCRSUBSAMPLING ; 
 int /*<<< orphan*/ * gtStripSeparate ; 
 int /*<<< orphan*/ * gtTileSeparate ; 
 int /*<<< orphan*/  initYCbCrConversion (TYPE_2__*) ; 
 int /*<<< orphan*/ * putCMYKseparate8bittile ; 
 int /*<<< orphan*/ * putRGBAAseparate16bittile ; 
 int /*<<< orphan*/ * putRGBAAseparate8bittile ; 
 int /*<<< orphan*/ * putRGBUAseparate16bittile ; 
 int /*<<< orphan*/ * putRGBUAseparate8bittile ; 
 int /*<<< orphan*/ * putRGBseparate16bittile ; 
 int /*<<< orphan*/ * putRGBseparate8bittile ; 
 int /*<<< orphan*/ * putseparate8bitYCbCr11tile ; 

__attribute__((used)) static int
PickSeparateCase(TIFFRGBAImage* img)
{
	img->get = TIFFIsTiled(img->tif) ? gtTileSeparate : gtStripSeparate;
	img->put.separate = NULL;
	switch (img->photometric) {
	case PHOTOMETRIC_MINISWHITE:
	case PHOTOMETRIC_MINISBLACK:
		/* greyscale images processed pretty much as RGB by gtTileSeparate */
	case PHOTOMETRIC_RGB:
		switch (img->bitspersample) {
		case 8:
			if (img->alpha == EXTRASAMPLE_ASSOCALPHA)
				img->put.separate = putRGBAAseparate8bittile;
			else if (img->alpha == EXTRASAMPLE_UNASSALPHA)
			{
				if (BuildMapUaToAa(img))
					img->put.separate = putRGBUAseparate8bittile;
			}
			else
				img->put.separate = putRGBseparate8bittile;
			break;
		case 16:
			if (img->alpha == EXTRASAMPLE_ASSOCALPHA)
			{
				if (BuildMapBitdepth16To8(img))
					img->put.separate = putRGBAAseparate16bittile;
			}
			else if (img->alpha == EXTRASAMPLE_UNASSALPHA)
			{
				if (BuildMapBitdepth16To8(img) &&
				    BuildMapUaToAa(img))
					img->put.separate = putRGBUAseparate16bittile;
			}
			else
			{
				if (BuildMapBitdepth16To8(img))
					img->put.separate = putRGBseparate16bittile;
			}
			break;
		}
		break;
	case PHOTOMETRIC_SEPARATED:
		if (img->bitspersample == 8 && img->samplesperpixel == 4)
		{
			img->alpha = 1; // Not alpha, but seems like the only way to get 4th band
			img->put.separate = putCMYKseparate8bittile;
		}
		break;
	case PHOTOMETRIC_YCBCR:
		if ((img->bitspersample==8) && (img->samplesperpixel==3))
		{
			if (initYCbCrConversion(img)!=0)
			{
				uint16 hs, vs;
				TIFFGetFieldDefaulted(img->tif, TIFFTAG_YCBCRSUBSAMPLING, &hs, &vs);
				switch ((hs<<4)|vs) {
				case 0x11:
					img->put.separate = putseparate8bitYCbCr11tile;
					break;
					/* TODO: add other cases here */
				}
			}
		}
		break;
	}
	return ((img->get!=NULL) && (img->put.separate!=NULL));
}