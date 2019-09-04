#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_11__ {scalar_t__ trueColor; } ;
struct TYPE_10__ {int* brushColorMap; TYPE_3__* brush; scalar_t__ trueColor; } ;

/* Variables and functions */
 int gdImageColorResolveAlpha (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gdImageGetPixel (TYPE_3__*,int,int) ; 
 int gdImageGetTransparent (TYPE_3__*) ; 
 int gdImageGetTrueColorPixel (TYPE_3__*,int,int) ; 
 int gdImageSX (TYPE_3__*) ; 
 int gdImageSY (TYPE_3__*) ; 
 int /*<<< orphan*/  gdImageSetPixel (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  gdTrueColorGetAlpha (int) ; 
 int /*<<< orphan*/  gdTrueColorGetBlue (int) ; 
 int /*<<< orphan*/  gdTrueColorGetGreen (int) ; 
 int /*<<< orphan*/  gdTrueColorGetRed (int) ; 

__attribute__((used)) static void gdImageBrushApply (gdImagePtr im, int x, int y)
{
	int lx, ly;
	int hy, hx;
	int x1, y1, x2, y2;
	int srcx, srcy;

	if (!im->brush) {
		return;
	}

	hy = gdImageSY(im->brush) / 2;
	y1 = y - hy;
	y2 = y1 + gdImageSY(im->brush);
	hx = gdImageSX(im->brush) / 2;
	x1 = x - hx;
	x2 = x1 + gdImageSX(im->brush);
	srcy = 0;

	if (im->trueColor) {
		if (im->brush->trueColor) {
			for (ly = y1; ly < y2; ly++) {
				srcx = 0;
				for (lx = x1; (lx < x2); lx++) {
					int p;
					p = gdImageGetTrueColorPixel(im->brush, srcx, srcy);
					/* 2.0.9, Thomas Winzig: apply simple full transparency */
					if (p != gdImageGetTransparent(im->brush)) {
						gdImageSetPixel(im, lx, ly, p);
					}
					srcx++;
				}
				srcy++;
			}
		} else {
			/* 2.0.12: Brush palette, image truecolor (thanks to Thorben Kundinger for pointing out the issue) */
			for (ly = y1; ly < y2; ly++) {
				srcx = 0;
				for (lx = x1; lx < x2; lx++) {
					int p, tc;
					p = gdImageGetPixel(im->brush, srcx, srcy);
					tc = gdImageGetTrueColorPixel(im->brush, srcx, srcy);
					/* 2.0.9, Thomas Winzig: apply simple full transparency */
					if (p != gdImageGetTransparent(im->brush)) {
						gdImageSetPixel(im, lx, ly, tc);
					}
					srcx++;
				}
				srcy++;
			}
		}
	} else {
		for (ly = y1; ly < y2; ly++) {
			srcx = 0;
			for (lx = x1; lx < x2; lx++) {
				int p;
				p = gdImageGetPixel(im->brush, srcx, srcy);
				/* Allow for non-square brushes! */
				if (p != gdImageGetTransparent(im->brush)) {
					/* Truecolor brush. Very slow on a palette destination. */
					if (im->brush->trueColor) {
						gdImageSetPixel(im, lx, ly, gdImageColorResolveAlpha(im, gdTrueColorGetRed(p),
													 gdTrueColorGetGreen(p),
													 gdTrueColorGetBlue(p),
													 gdTrueColorGetAlpha(p)));
					} else {
						gdImageSetPixel(im, lx, ly, im->brushColorMap[p]);
					}
				}
				srcx++;
			}
			srcy++;
		}
	}
}