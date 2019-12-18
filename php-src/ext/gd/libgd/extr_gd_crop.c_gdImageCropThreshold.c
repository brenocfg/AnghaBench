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
 scalar_t__ gdColorMatch (int /*<<< orphan*/ *,unsigned int const,int /*<<< orphan*/ ,float const) ; 
 unsigned int const gdImageColorsTotal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gdImageCrop (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gdImageGetPixel (int /*<<< orphan*/ *,int,int) ; 
 int gdImageSX (int /*<<< orphan*/ *) ; 
 int gdImageSY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdImageTrueColor (int /*<<< orphan*/ *) ; 

gdImagePtr gdImageCropThreshold(gdImagePtr im, const unsigned int color, const float threshold)
{
	const int width = gdImageSX(im);
	const int height = gdImageSY(im);

	int x,y;
	int match;
	gdRect crop;

	crop.x = 0;
	crop.y = 0;
	crop.width = 0;
	crop.height = 0;

	/* Pierre: crop everything sounds bad */
	if (threshold > 100.0) {
		return NULL;
	}

	if (!gdImageTrueColor(im) && color >= gdImageColorsTotal(im)) {
		return NULL;
	}

	/* TODO: Add gdImageGetRowPtr and works with ptr at the row level
	 * for the true color and palette images
	 * new formats will simply work with ptr
	 */
	match = 1;
	for (y = 0; match && y < height; y++) {
		for (x = 0; match && x < width; x++) {
			match = (gdColorMatch(im, color, gdImageGetPixel(im, x,y), threshold)) > 0;
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
			match = (gdColorMatch(im, color, gdImageGetPixel(im, x, y), threshold)) > 0;
		}
	}
	crop.height = y - crop.y + 2;

	match = 1;
	for (x = 0; match && x < width; x++) {
		for (y = 0; match && y < crop.y + crop.height; y++) {
			match = (gdColorMatch(im, color, gdImageGetPixel(im, x,y), threshold)) > 0;
		}
	}
	crop.x = x - 1;

	match = 1;
	for (x = width - 1; match && x >= 0; x--) {
		for (y = 0; match &&  y < crop.y + crop.height; y++) {
			match = (gdColorMatch(im, color, gdImageGetPixel(im, x,y), threshold)) > 0;
		}
	}
	crop.width = x - crop.x + 2;

	return gdImageCrop(im, &crop);
}