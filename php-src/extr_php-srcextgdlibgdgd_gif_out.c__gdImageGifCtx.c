#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtxPtr ;
struct TYPE_7__ {int interlace; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  transparent; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; int /*<<< orphan*/  colorsTotal; scalar_t__ trueColor; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIFEncode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int colorstobpp (int /*<<< orphan*/ ) ; 
 TYPE_1__* gdImageCreatePaletteFromTrueColor (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  gdImageDestroy (TYPE_1__*) ; 

__attribute__((used)) static int _gdImageGifCtx(gdImagePtr im, gdIOCtxPtr out)
{
	gdImagePtr pim = 0, tim = im;
	int interlace, BitsPerPixel;
	interlace = im->interlace;
	if (im->trueColor) {
		/* Expensive, but the only way that produces an
			acceptable result: mix down to a palette
			based temporary image. */
		pim = gdImageCreatePaletteFromTrueColor(im, 1, 256);
		if (!pim) {
			return 1;
		}
		tim = pim;
	}
	BitsPerPixel = colorstobpp(tim->colorsTotal);
	/* All set, let's do it. */
	GIFEncode(
		out, tim->sx, tim->sy, interlace, 0, tim->transparent, BitsPerPixel,
		tim->red, tim->green, tim->blue, tim);
	if (pim) {
		/* Destroy palette based temporary image. */
		gdImageDestroy(	pim);
	}

    return 0;
}