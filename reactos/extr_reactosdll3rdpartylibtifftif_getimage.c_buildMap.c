#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_8__ {int photometric; int bitspersample; TYPE_7__* tif; } ;
typedef  TYPE_1__ TIFFRGBAImage ;

/* Variables and functions */
#define  PHOTOMETRIC_MINISBLACK 133 
#define  PHOTOMETRIC_MINISWHITE 132 
#define  PHOTOMETRIC_PALETTE 131 
#define  PHOTOMETRIC_RGB 130 
#define  PHOTOMETRIC_SEPARATED 129 
#define  PHOTOMETRIC_YCBCR 128 
 int /*<<< orphan*/  TIFFFileName (TYPE_7__*) ; 
 int /*<<< orphan*/  TIFFWarningExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int checkcmap (TYPE_1__*) ; 
 int /*<<< orphan*/  cvtcmap (TYPE_1__*) ; 
 int /*<<< orphan*/  makecmap (TYPE_1__*) ; 
 int /*<<< orphan*/  setupMap (TYPE_1__*) ; 

__attribute__((used)) static int
buildMap(TIFFRGBAImage* img)
{
    switch (img->photometric) {
    case PHOTOMETRIC_RGB:
    case PHOTOMETRIC_YCBCR:
    case PHOTOMETRIC_SEPARATED:
	if (img->bitspersample == 8)
	    break;
	/* fall through... */
    case PHOTOMETRIC_MINISBLACK:
    case PHOTOMETRIC_MINISWHITE:
	if (!setupMap(img))
	    return (0);
	break;
    case PHOTOMETRIC_PALETTE:
	/*
	 * Convert 16-bit colormap to 8-bit (unless it looks
	 * like an old-style 8-bit colormap).
	 */
	if (checkcmap(img) == 16)
	    cvtcmap(img);
	else
	    TIFFWarningExt(img->tif->tif_clientdata, TIFFFileName(img->tif), "Assuming 8-bit colormap");
	/*
	 * Use mapping table and colormap to construct
	 * unpacking tables for samples < 8 bits.
	 */
	if (img->bitspersample <= 8 && !makecmap(img))
	    return (0);
	break;
    }
    return (1);
}