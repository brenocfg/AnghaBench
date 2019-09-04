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
typedef  int uint16 ;
struct TYPE_9__ {int /*<<< orphan*/ * contig; } ;
struct TYPE_10__ {int photometric; int bitspersample; int samplesperpixel; TYPE_1__ put; int /*<<< orphan*/ * get; int /*<<< orphan*/  tif; int /*<<< orphan*/  alpha; int /*<<< orphan*/  Map; } ;
typedef  TYPE_2__ TIFFRGBAImage ;

/* Variables and functions */
 int /*<<< orphan*/  BuildMapBitdepth16To8 (TYPE_2__*) ; 
 int /*<<< orphan*/  BuildMapUaToAa (TYPE_2__*) ; 
 int /*<<< orphan*/  EXTRASAMPLE_ASSOCALPHA ; 
 int /*<<< orphan*/  EXTRASAMPLE_UNASSALPHA ; 
#define  PHOTOMETRIC_CIELAB 134 
#define  PHOTOMETRIC_MINISBLACK 133 
#define  PHOTOMETRIC_MINISWHITE 132 
#define  PHOTOMETRIC_PALETTE 131 
#define  PHOTOMETRIC_RGB 130 
#define  PHOTOMETRIC_SEPARATED 129 
#define  PHOTOMETRIC_YCBCR 128 
 int /*<<< orphan*/  TIFFGetFieldDefaulted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ TIFFIsTiled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFTAG_YCBCRSUBSAMPLING ; 
 int /*<<< orphan*/  buildMap (TYPE_2__*) ; 
 int /*<<< orphan*/ * gtStripContig ; 
 int /*<<< orphan*/ * gtTileContig ; 
 int /*<<< orphan*/ * initCIELabConversion (TYPE_2__*) ; 
 int /*<<< orphan*/  initYCbCrConversion (TYPE_2__*) ; 
 int /*<<< orphan*/ * put16bitbwtile ; 
 int /*<<< orphan*/ * put1bitbwtile ; 
 int /*<<< orphan*/ * put1bitcmaptile ; 
 int /*<<< orphan*/ * put2bitbwtile ; 
 int /*<<< orphan*/ * put2bitcmaptile ; 
 int /*<<< orphan*/ * put4bitbwtile ; 
 int /*<<< orphan*/ * put4bitcmaptile ; 
 int /*<<< orphan*/ * put8bitcmaptile ; 
 int /*<<< orphan*/ * putRGBAAcontig16bittile ; 
 int /*<<< orphan*/ * putRGBAAcontig8bittile ; 
 int /*<<< orphan*/ * putRGBUAcontig16bittile ; 
 int /*<<< orphan*/ * putRGBUAcontig8bittile ; 
 int /*<<< orphan*/ * putRGBcontig16bittile ; 
 int /*<<< orphan*/ * putRGBcontig8bitCMYKMaptile ; 
 int /*<<< orphan*/ * putRGBcontig8bitCMYKtile ; 
 int /*<<< orphan*/ * putRGBcontig8bittile ; 
 int /*<<< orphan*/ * putagreytile ; 
 int /*<<< orphan*/ * putcontig8bitYCbCr11tile ; 
 int /*<<< orphan*/ * putcontig8bitYCbCr12tile ; 
 int /*<<< orphan*/ * putcontig8bitYCbCr21tile ; 
 int /*<<< orphan*/ * putcontig8bitYCbCr22tile ; 
 int /*<<< orphan*/ * putcontig8bitYCbCr41tile ; 
 int /*<<< orphan*/ * putcontig8bitYCbCr42tile ; 
 int /*<<< orphan*/ * putcontig8bitYCbCr44tile ; 
 int /*<<< orphan*/ * putgreytile ; 

__attribute__((used)) static int
PickContigCase(TIFFRGBAImage* img)
{
	img->get = TIFFIsTiled(img->tif) ? gtTileContig : gtStripContig;
	img->put.contig = NULL;
	switch (img->photometric) {
		case PHOTOMETRIC_RGB:
			switch (img->bitspersample) {
				case 8:
					if (img->alpha == EXTRASAMPLE_ASSOCALPHA &&
						img->samplesperpixel >= 4)
						img->put.contig = putRGBAAcontig8bittile;
					else if (img->alpha == EXTRASAMPLE_UNASSALPHA &&
							 img->samplesperpixel >= 4)
					{
						if (BuildMapUaToAa(img))
							img->put.contig = putRGBUAcontig8bittile;
					}
					else if( img->samplesperpixel >= 3 )
						img->put.contig = putRGBcontig8bittile;
					break;
				case 16:
					if (img->alpha == EXTRASAMPLE_ASSOCALPHA &&
						img->samplesperpixel >=4 )
					{
						if (BuildMapBitdepth16To8(img))
							img->put.contig = putRGBAAcontig16bittile;
					}
					else if (img->alpha == EXTRASAMPLE_UNASSALPHA &&
							 img->samplesperpixel >=4 )
					{
						if (BuildMapBitdepth16To8(img) &&
						    BuildMapUaToAa(img))
							img->put.contig = putRGBUAcontig16bittile;
					}
					else if( img->samplesperpixel >=3 )
					{
						if (BuildMapBitdepth16To8(img))
							img->put.contig = putRGBcontig16bittile;
					}
					break;
			}
			break;
		case PHOTOMETRIC_SEPARATED:
			if (img->samplesperpixel >=4 && buildMap(img)) {
				if (img->bitspersample == 8) {
					if (!img->Map)
						img->put.contig = putRGBcontig8bitCMYKtile;
					else
						img->put.contig = putRGBcontig8bitCMYKMaptile;
				}
			}
			break;
		case PHOTOMETRIC_PALETTE:
			if (buildMap(img)) {
				switch (img->bitspersample) {
					case 8:
						img->put.contig = put8bitcmaptile;
						break;
					case 4:
						img->put.contig = put4bitcmaptile;
						break;
					case 2:
						img->put.contig = put2bitcmaptile;
						break;
					case 1:
						img->put.contig = put1bitcmaptile;
						break;
				}
			}
			break;
		case PHOTOMETRIC_MINISWHITE:
		case PHOTOMETRIC_MINISBLACK:
			if (buildMap(img)) {
				switch (img->bitspersample) {
					case 16:
						img->put.contig = put16bitbwtile;
						break;
					case 8:
						if (img->alpha && img->samplesperpixel == 2)
							img->put.contig = putagreytile;
						else
							img->put.contig = putgreytile;
						break;
					case 4:
						img->put.contig = put4bitbwtile;
						break;
					case 2:
						img->put.contig = put2bitbwtile;
						break;
					case 1:
						img->put.contig = put1bitbwtile;
						break;
				}
			}
			break;
		case PHOTOMETRIC_YCBCR:
			if ((img->bitspersample==8) && (img->samplesperpixel==3))
			{
				if (initYCbCrConversion(img)!=0)
				{
					/*
					 * The 6.0 spec says that subsampling must be
					 * one of 1, 2, or 4, and that vertical subsampling
					 * must always be <= horizontal subsampling; so
					 * there are only a few possibilities and we just
					 * enumerate the cases.
					 * Joris: added support for the [1,2] case, nonetheless, to accommodate
					 * some OJPEG files
					 */
					uint16 SubsamplingHor;
					uint16 SubsamplingVer;
					TIFFGetFieldDefaulted(img->tif, TIFFTAG_YCBCRSUBSAMPLING, &SubsamplingHor, &SubsamplingVer);
					switch ((SubsamplingHor<<4)|SubsamplingVer) {
						case 0x44:
							img->put.contig = putcontig8bitYCbCr44tile;
							break;
						case 0x42:
							img->put.contig = putcontig8bitYCbCr42tile;
							break;
						case 0x41:
							img->put.contig = putcontig8bitYCbCr41tile;
							break;
						case 0x22:
							img->put.contig = putcontig8bitYCbCr22tile;
							break;
						case 0x21:
							img->put.contig = putcontig8bitYCbCr21tile;
							break;
						case 0x12:
							img->put.contig = putcontig8bitYCbCr12tile;
							break;
						case 0x11:
							img->put.contig = putcontig8bitYCbCr11tile;
							break;
					}
				}
			}
			break;
		case PHOTOMETRIC_CIELAB:
			if (img->samplesperpixel == 3 && buildMap(img)) {
				if (img->bitspersample == 8)
					img->put.contig = initCIELabConversion(img);
				break;
			}
	}
	return ((img->get!=NULL) && (img->put.contig!=NULL));
}