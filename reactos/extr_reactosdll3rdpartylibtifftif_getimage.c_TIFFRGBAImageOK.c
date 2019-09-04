#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_6__ {int td_bitspersample; scalar_t__ td_sampleformat; int td_samplesperpixel; int td_extrasamples; int td_planarconfig; int td_compression; } ;
struct TYPE_7__ {int /*<<< orphan*/  tif_decodestatus; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int COMPRESSION_SGILOG ; 
 int COMPRESSION_SGILOG24 ; 
 int INKSET_CMYK ; 
#define  PHOTOMETRIC_CIELAB 136 
#define  PHOTOMETRIC_LOGL 135 
#define  PHOTOMETRIC_LOGLUV 134 
#define  PHOTOMETRIC_MINISBLACK 133 
#define  PHOTOMETRIC_MINISWHITE 132 
#define  PHOTOMETRIC_PALETTE 131 
#define  PHOTOMETRIC_RGB 130 
#define  PHOTOMETRIC_SEPARATED 129 
#define  PHOTOMETRIC_YCBCR 128 
 int PLANARCONFIG_CONTIG ; 
 scalar_t__ SAMPLEFORMAT_IEEEFP ; 
 int /*<<< orphan*/  TIFFGetField (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TIFFGetFieldDefaulted (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TIFFTAG_INKSET ; 
 int /*<<< orphan*/  TIFFTAG_PHOTOMETRIC ; 
 char* photoTag ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

int
TIFFRGBAImageOK(TIFF* tif, char emsg[1024])
{
	TIFFDirectory* td = &tif->tif_dir;
	uint16 photometric;
	int colorchannels;

	if (!tif->tif_decodestatus) {
		sprintf(emsg, "Sorry, requested compression method is not configured");
		return (0);
	}
	switch (td->td_bitspersample) {
		case 1:
		case 2:
		case 4:
		case 8:
		case 16:
			break;
		default:
			sprintf(emsg, "Sorry, can not handle images with %d-bit samples",
			    td->td_bitspersample);
			return (0);
	}
        if (td->td_sampleformat == SAMPLEFORMAT_IEEEFP) {
                sprintf(emsg, "Sorry, can not handle images with IEEE floating-point samples");
                return (0);
        }
	colorchannels = td->td_samplesperpixel - td->td_extrasamples;
	if (!TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &photometric)) {
		switch (colorchannels) {
			case 1:
				photometric = PHOTOMETRIC_MINISBLACK;
				break;
			case 3:
				photometric = PHOTOMETRIC_RGB;
				break;
			default:
				sprintf(emsg, "Missing needed %s tag", photoTag);
				return (0);
		}
	}
	switch (photometric) {
		case PHOTOMETRIC_MINISWHITE:
		case PHOTOMETRIC_MINISBLACK:
		case PHOTOMETRIC_PALETTE:
			if (td->td_planarconfig == PLANARCONFIG_CONTIG
			    && td->td_samplesperpixel != 1
			    && td->td_bitspersample < 8 ) {
				sprintf(emsg,
				    "Sorry, can not handle contiguous data with %s=%d, "
				    "and %s=%d and Bits/Sample=%d",
				    photoTag, photometric,
				    "Samples/pixel", td->td_samplesperpixel,
				    td->td_bitspersample);
				return (0);
			}
			/*
			 * We should likely validate that any extra samples are either
			 * to be ignored, or are alpha, and if alpha we should try to use
			 * them.  But for now we won't bother with this.
			*/
			break;
		case PHOTOMETRIC_YCBCR:
			/*
			 * TODO: if at all meaningful and useful, make more complete
			 * support check here, or better still, refactor to let supporting
			 * code decide whether there is support and what meaningful
			 * error to return
			 */
			break;
		case PHOTOMETRIC_RGB:
			if (colorchannels < 3) {
				sprintf(emsg, "Sorry, can not handle RGB image with %s=%d",
				    "Color channels", colorchannels);
				return (0);
			}
			break;
		case PHOTOMETRIC_SEPARATED:
			{
				uint16 inkset;
				TIFFGetFieldDefaulted(tif, TIFFTAG_INKSET, &inkset);
				if (inkset != INKSET_CMYK) {
					sprintf(emsg,
					    "Sorry, can not handle separated image with %s=%d",
					    "InkSet", inkset);
					return 0;
				}
				if (td->td_samplesperpixel < 4) {
					sprintf(emsg,
					    "Sorry, can not handle separated image with %s=%d",
					    "Samples/pixel", td->td_samplesperpixel);
					return 0;
				}
				break;
			}
		case PHOTOMETRIC_LOGL:
			if (td->td_compression != COMPRESSION_SGILOG) {
				sprintf(emsg, "Sorry, LogL data must have %s=%d",
				    "Compression", COMPRESSION_SGILOG);
				return (0);
			}
			break;
		case PHOTOMETRIC_LOGLUV:
			if (td->td_compression != COMPRESSION_SGILOG &&
			    td->td_compression != COMPRESSION_SGILOG24) {
				sprintf(emsg, "Sorry, LogLuv data must have %s=%d or %d",
				    "Compression", COMPRESSION_SGILOG, COMPRESSION_SGILOG24);
				return (0);
			}
			if (td->td_planarconfig != PLANARCONFIG_CONTIG) {
				sprintf(emsg, "Sorry, can not handle LogLuv images with %s=%d",
				    "Planarconfiguration", td->td_planarconfig);
				return (0);
			}
			if ( td->td_samplesperpixel != 3 || colorchannels != 3 ) {
                                sprintf(emsg,
                                        "Sorry, can not handle image with %s=%d, %s=%d",
                                        "Samples/pixel", td->td_samplesperpixel,
                                        "colorchannels", colorchannels);
                                return 0;
                        }
			break;
		case PHOTOMETRIC_CIELAB:
                        if ( td->td_samplesperpixel != 3 || colorchannels != 3 || td->td_bitspersample != 8 ) {
                                sprintf(emsg,
                                        "Sorry, can not handle image with %s=%d, %s=%d and %s=%d",
                                        "Samples/pixel", td->td_samplesperpixel,
                                        "colorchannels", colorchannels,
                                        "Bits/sample", td->td_bitspersample);
                                return 0;
                        }
			break;
                default:
			sprintf(emsg, "Sorry, can not handle image with %s=%d",
			    photoTag, photometric);
			return (0);
	}
	return (1);
}