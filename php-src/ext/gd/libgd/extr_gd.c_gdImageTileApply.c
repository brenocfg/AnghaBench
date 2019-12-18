#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_9__ {int* tileColorMap; scalar_t__ trueColor; int /*<<< orphan*/ * alpha; int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; struct TYPE_9__* tile; } ;

/* Variables and functions */
 int gdImageColorResolveAlpha (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gdImageGetPixel (TYPE_1__*,int,int) ; 
 int gdImageGetTransparent (TYPE_1__*) ; 
 int gdImageSX (TYPE_1__*) ; 
 int gdImageSY (TYPE_1__*) ; 
 int /*<<< orphan*/  gdImageSetPixel (TYPE_1__*,int,int,int) ; 
 int gdTrueColorAlpha (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdTrueColorGetAlpha (int) ; 
 int /*<<< orphan*/  gdTrueColorGetBlue (int) ; 
 int /*<<< orphan*/  gdTrueColorGetGreen (int) ; 
 int /*<<< orphan*/  gdTrueColorGetRed (int) ; 

__attribute__((used)) static void gdImageTileApply (gdImagePtr im, int x, int y)
{
	gdImagePtr tile = im->tile;
	int srcx, srcy;
	int p;
	if (!tile) {
		return;
	}
	srcx = x % gdImageSX(tile);
	srcy = y % gdImageSY(tile);
	if (im->trueColor) {
		p = gdImageGetPixel(tile, srcx, srcy);
		if (p != gdImageGetTransparent (tile)) {
			if (!tile->trueColor) {
				p = gdTrueColorAlpha(tile->red[p], tile->green[p], tile->blue[p], tile->alpha[p]);
			}
			gdImageSetPixel(im, x, y, p);
		}
	} else {
		p = gdImageGetPixel(tile, srcx, srcy);
		/* Allow for transparency */
		if (p != gdImageGetTransparent(tile)) {
			if (tile->trueColor) {
				/* Truecolor tile. Very slow on a palette destination. */
				gdImageSetPixel(im, x, y, gdImageColorResolveAlpha(im,
											gdTrueColorGetRed(p),
											gdTrueColorGetGreen(p),
											gdTrueColorGetBlue(p),
											gdTrueColorGetAlpha(p)));
			} else {
				gdImageSetPixel(im, x, y, im->tileColorMap[p]);
			}
		}
	}
}