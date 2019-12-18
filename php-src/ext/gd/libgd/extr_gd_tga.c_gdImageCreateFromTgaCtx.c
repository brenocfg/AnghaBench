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
struct TYPE_13__ {int* bitmap; int width; int height; scalar_t__ bits; scalar_t__ fliph; scalar_t__ flipv; scalar_t__ alphabits; int /*<<< orphan*/ * ident; } ;
typedef  TYPE_1__ oTga ;
typedef  TYPE_2__* gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_14__ {int** tpixels; } ;

/* Variables and functions */
 scalar_t__ TGA_BPP_24 ; 
 scalar_t__ TGA_BPP_32 ; 
 int /*<<< orphan*/  free_tga (TYPE_1__*) ; 
 scalar_t__ gdAlphaMax ; 
 int /*<<< orphan*/  gdImageAlphaBlending (TYPE_2__* volatile,int /*<<< orphan*/ ) ; 
 TYPE_2__* gdImageCreateTrueColor (int,int) ; 
 int /*<<< orphan*/  gdImageFlipBoth (TYPE_2__* volatile) ; 
 int /*<<< orphan*/  gdImageFlipHorizontal (TYPE_2__* volatile) ; 
 int /*<<< orphan*/  gdImageFlipVertical (TYPE_2__* volatile) ; 
 int /*<<< orphan*/  gdImageSaveAlpha (TYPE_2__* volatile,int) ; 
 scalar_t__ gdMalloc (int) ; 
 int gdTrueColor (int,int,int) ; 
 int gdTrueColorAlpha (int,int,int,scalar_t__) ; 
 scalar_t__ read_header_tga (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ read_image_tga (int /*<<< orphan*/ *,TYPE_1__*) ; 

gdImagePtr gdImageCreateFromTgaCtx(gdIOCtx* ctx)
{
	int bitmap_caret = 0;
	oTga *tga = NULL;
	/*	int pixel_block_size = 0;
		int image_block_size = 0; */
	volatile gdImagePtr image = NULL;
	int x = 0;
	int y = 0;

	tga = (oTga *) gdMalloc(sizeof(oTga));
	if (!tga) {
		return NULL;
	}

	tga->bitmap = NULL;
	tga->ident = NULL;

	if (read_header_tga(ctx, tga) < 0) {
		free_tga(tga);
		return NULL;
	}

	/*TODO: Will this be used?
		pixel_block_size = tga->bits / 8;
		image_block_size = (tga->width * tga->height) * pixel_block_size;
	*/

	if (read_image_tga(ctx, tga) < 0) {
		free_tga(tga);
		return NULL;
	}

	image = gdImageCreateTrueColor((int)tga->width, (int)tga->height );

	if (image == 0) {
		free_tga( tga );
		return NULL;
	}

	/*!	\brief Populate GD image object
	 *  Copy the pixel data from our tga bitmap buffer into the GD image
	 *  Disable blending and save the alpha channel per default
	 */
	if (tga->alphabits) {
		gdImageAlphaBlending(image, 0);
		gdImageSaveAlpha(image, 1);
	}

	/* TODO: use alphabits as soon as we support 24bit and other alpha bps (ie != 8bits) */
	for (y = 0; y < tga->height; y++) {
		register int *tpix = image->tpixels[y];
		for ( x = 0; x < tga->width; x++, tpix++) {
			if (tga->bits == TGA_BPP_24) {
				*tpix = gdTrueColor(tga->bitmap[bitmap_caret + 2], tga->bitmap[bitmap_caret + 1], tga->bitmap[bitmap_caret]);
				bitmap_caret += 3;
			} else if (tga->bits == TGA_BPP_32 && tga->alphabits) {
				register int a = tga->bitmap[bitmap_caret + 3];

				*tpix = gdTrueColorAlpha(tga->bitmap[bitmap_caret + 2], tga->bitmap[bitmap_caret + 1], tga->bitmap[bitmap_caret], gdAlphaMax - (a >> 1));
				bitmap_caret += 4;
			}
		}
	}

	if (tga->flipv && tga->fliph) {
		gdImageFlipBoth(image);
	} else if (tga->flipv) {
		gdImageFlipVertical(image);
	} else if (tga->fliph) {
		gdImageFlipHorizontal(image);
	}

	free_tga(tga);

	return image;
}