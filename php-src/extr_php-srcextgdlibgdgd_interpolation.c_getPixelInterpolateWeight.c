#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_5__ {int trueColor; double const* red; double const* green; double const* blue; double const* alpha; } ;

/* Variables and functions */
 int CLAMP (int,int /*<<< orphan*/ ,int) ; 
 int gdAlphaMax ; 
 int gdTrueColorAlpha (int,int,int,int) ; 
 double const gdTrueColorGetAlpha (int const) ; 
 double const gdTrueColorGetBlue (int const) ; 
 double const gdTrueColorGetGreen (int const) ; 
 double const gdTrueColorGetRed (int const) ; 
 int getPixelOverflowPalette (TYPE_1__*,int,int,int const) ; 
 int getPixelOverflowTC (TYPE_1__*,int,int,int const) ; 

__attribute__((used)) static int getPixelInterpolateWeight(gdImagePtr im, const double x, const double y, const int bgColor)
{
	/* Closest pixel <= (xf,yf) */
	int sx = (int)(x);
	int sy = (int)(y);
	const double xf = x - (double)sx;
	const double yf = y - (double)sy;
	const double nxf = (double) 1.0 - xf;
	const double nyf = (double) 1.0 - yf;
	const double m1 = xf * yf;
	const double m2 = nxf * yf;
	const double m3 = xf * nyf;
	const double m4 = nxf * nyf;

	/* get color values of neighbouring pixels */
	const int c1 = im->trueColor == 1 ? getPixelOverflowTC(im, sx, sy, bgColor)         : getPixelOverflowPalette(im, sx, sy, bgColor);
	const int c2 = im->trueColor == 1 ? getPixelOverflowTC(im, sx - 1, sy, bgColor)     : getPixelOverflowPalette(im, sx - 1, sy, bgColor);
	const int c3 = im->trueColor == 1 ? getPixelOverflowTC(im, sx, sy - 1, bgColor)     : getPixelOverflowPalette(im, sx, sy - 1, bgColor);
	const int c4 = im->trueColor == 1 ? getPixelOverflowTC(im, sx - 1, sy - 1, bgColor) : getPixelOverflowPalette(im, sx, sy - 1, bgColor);
	int r, g, b, a;

	if (x < 0) sx--;
	if (y < 0) sy--;

	/* component-wise summing-up of color values */
	if (im->trueColor) {
		r = (int)(m1*gdTrueColorGetRed(c1)   + m2*gdTrueColorGetRed(c2)   + m3*gdTrueColorGetRed(c3)   + m4*gdTrueColorGetRed(c4));
		g = (int)(m1*gdTrueColorGetGreen(c1) + m2*gdTrueColorGetGreen(c2) + m3*gdTrueColorGetGreen(c3) + m4*gdTrueColorGetGreen(c4));
		b = (int)(m1*gdTrueColorGetBlue(c1)  + m2*gdTrueColorGetBlue(c2)  + m3*gdTrueColorGetBlue(c3)  + m4*gdTrueColorGetBlue(c4));
		a = (int)(m1*gdTrueColorGetAlpha(c1) + m2*gdTrueColorGetAlpha(c2) + m3*gdTrueColorGetAlpha(c3) + m4*gdTrueColorGetAlpha(c4));
	} else {
		r = (int)(m1*im->red[(c1)]   + m2*im->red[(c2)]   + m3*im->red[(c3)]   + m4*im->red[(c4)]);
		g = (int)(m1*im->green[(c1)] + m2*im->green[(c2)] + m3*im->green[(c3)] + m4*im->green[(c4)]);
		b = (int)(m1*im->blue[(c1)]  + m2*im->blue[(c2)]  + m3*im->blue[(c3)]  + m4*im->blue[(c4)]);
		a = (int)(m1*im->alpha[(c1)] + m2*im->alpha[(c2)] + m3*im->alpha[(c3)] + m4*im->alpha[(c4)]);
	}

	r = CLAMP(r, 0, 255);
	g = CLAMP(g, 0, 255);
	b = CLAMP(b, 0, 255);
	a = CLAMP(a, 0, gdAlphaMax);
	return gdTrueColorAlpha(r, g, b, a);
}