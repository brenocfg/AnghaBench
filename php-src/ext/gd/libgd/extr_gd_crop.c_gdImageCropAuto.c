#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int x; int y; int width; int height; } ;
typedef  TYPE_1__ gdRect ;
typedef  int /*<<< orphan*/ * gdImagePtr ;

/* Variables and functions */
#define  GD_CROP_BLACK 132 
#define  GD_CROP_DEFAULT 131 
#define  GD_CROP_SIDES 130 
#define  GD_CROP_TRANSPARENT 129 
#define  GD_CROP_WHITE 128 
 int /*<<< orphan*/  gdGuessBackgroundColorFromCorners (int /*<<< orphan*/ *,int*) ; 
 int gdImageColorClosestAlpha (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gdImageCrop (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int gdImageGetPixel (int /*<<< orphan*/ *,int,int) ; 
 int gdImageGetTransparent (int /*<<< orphan*/ *) ; 
 int gdImageSX (int /*<<< orphan*/ *) ; 
 int gdImageSY (int /*<<< orphan*/ *) ; 

gdImagePtr gdImageCropAuto(gdImagePtr im, const unsigned int mode)
{
	const int width = gdImageSX(im);
	const int height = gdImageSY(im);

	int x,y;
	int color, match;
	gdRect crop;

	crop.x = 0;
	crop.y = 0;
	crop.width = 0;
	crop.height = 0;

	switch (mode) {
		case GD_CROP_TRANSPARENT:
			color = gdImageGetTransparent(im);
			break;

		case GD_CROP_BLACK:
			color = gdImageColorClosestAlpha(im, 0, 0, 0, 0);
			break;

		case GD_CROP_WHITE:
			color = gdImageColorClosestAlpha(im, 255, 255, 255, 0);
			break;

		case GD_CROP_SIDES:
			gdGuessBackgroundColorFromCorners(im, &color);
			break;

		case GD_CROP_DEFAULT:
		default:
			color = gdImageGetTransparent(im);
			break;
	}

	/* TODO: Add gdImageGetRowPtr and works with ptr at the row level
	 * for the true color and palette images
	 * new formats will simply work with ptr
	 */
	match = 1;
	for (y = 0; match && y < height; y++) {
		for (x = 0; match && x < width; x++) {
			int c2 = gdImageGetPixel(im, x, y);
			match = (color == c2);
		}
	}

	/* Whole image would be cropped > bye */
	if (match) {
		return NULL;
	}

	crop.y = y - 1;

	match = 1;
	for (y = height - 1; match && y >= 0; y--) {
		for (x = 0; match && x < width; x++) {
			match = (color == gdImageGetPixel(im, x,y));
		}
	}
	crop.height = y - crop.y + 2;

	match = 1;
	for (x = 0; match && x < width; x++) {
		for (y = 0; match && y < crop.y + crop.height; y++) {
			match = (color == gdImageGetPixel(im, x,y));
		}
	}
	crop.x = x - 1;

	match = 1;
	for (x = width - 1; match && x >= 0; x--) {
		for (y = 0; match &&  y < crop.y + crop.height; y++) {
			match = (color == gdImageGetPixel(im, x,y));
		}
	}
	crop.width = x - crop.x + 2;

	return gdImageCrop(im, &crop);
}