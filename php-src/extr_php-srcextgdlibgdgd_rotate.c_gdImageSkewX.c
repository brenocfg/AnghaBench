#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_11__ {int sx; int transparent; scalar_t__ trueColor; } ;
typedef  int (* FuncPtr ) (gdImagePtr,int,int) ;

/* Variables and functions */
 double gdImageAlpha (TYPE_1__*,int) ; 
 double gdImageBlue (TYPE_1__*,int) ; 
 int gdImageColorAllocateAlpha (TYPE_1__*,int,int,int,int) ; 
 int gdImageColorClosestAlpha (TYPE_1__*,int,int,int,int) ; 
 int gdImageGetPixel (gdImagePtr,int,int) ; 
 int gdImageGetTrueColorPixel (gdImagePtr,int,int) ; 
 double gdImageGreen (TYPE_1__*,int) ; 
 double gdImageRed (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gdImageSetPixel (TYPE_1__*,int,int,int) ; 
 int gdTrueColorAlpha (int,int,int,int) ; 

void gdImageSkewX (gdImagePtr dst, gdImagePtr src, int uRow, int iOffset, double dWeight, int clrBack, int ignoretransparent)
{
	typedef int (*FuncPtr)(gdImagePtr, int, int);
	int i, r, g, b, a, clrBackR, clrBackG, clrBackB, clrBackA;
	FuncPtr f;

	int pxlOldLeft, pxlLeft=0, pxlSrc;

	/* Keep clrBack as color index if required */
	if (src->trueColor) {
		pxlOldLeft = clrBack;
		f = gdImageGetTrueColorPixel;
	} else {
		pxlOldLeft = clrBack;
		clrBackR = gdImageRed(src, clrBack);
		clrBackG = gdImageGreen(src, clrBack);
		clrBackB = gdImageBlue(src, clrBack);
		clrBackA = gdImageAlpha(src, clrBack);
		clrBack =  gdTrueColorAlpha(clrBackR, clrBackG, clrBackB, clrBackA);
		f = gdImageGetPixel;
	}

	for (i = 0; i < iOffset; i++) {
		gdImageSetPixel (dst, i, uRow, clrBack);
	}

	if (i < dst->sx) {
		gdImageSetPixel (dst, i, uRow, clrBack);
	}

	for (i = 0; i < src->sx; i++) {
		pxlSrc = f (src,i,uRow);

		r = (int)(gdImageRed(src,pxlSrc) * dWeight);
		g = (int)(gdImageGreen(src,pxlSrc) * dWeight);
		b = (int)(gdImageBlue(src,pxlSrc) * dWeight);
		a = (int)(gdImageAlpha(src,pxlSrc) * dWeight);

		pxlLeft = gdImageColorAllocateAlpha(src, r, g, b, a);

		if (pxlLeft == -1) {
			pxlLeft = gdImageColorClosestAlpha(src, r, g, b, a);
		}

		r = gdImageRed(src,pxlSrc) - (gdImageRed(src,pxlLeft) - gdImageRed(src,pxlOldLeft));
		g = gdImageGreen(src,pxlSrc) - (gdImageGreen(src,pxlLeft) - gdImageGreen(src,pxlOldLeft));
		b = gdImageBlue(src,pxlSrc) - (gdImageBlue(src,pxlLeft) - gdImageBlue(src,pxlOldLeft));
		a = gdImageAlpha(src,pxlSrc) - (gdImageAlpha(src,pxlLeft) - gdImageAlpha(src,pxlOldLeft));

        if (r>255) {
        	r = 255;
        }

		if (g>255) {
			g = 255;
		}

		if (b>255) {
			b = 255;
		}

		if (a>127) {
			a = 127;
		}

		if (ignoretransparent && pxlSrc == dst->transparent) {
			pxlSrc = dst->transparent;
		} else {
			pxlSrc = gdImageColorAllocateAlpha(dst, r, g, b, a);

			if (pxlSrc == -1) {
				pxlSrc = gdImageColorClosestAlpha(dst, r, g, b, a);
			}
		}

		if ((i + iOffset >= 0) && (i + iOffset < dst->sx)) {
			gdImageSetPixel (dst, i+iOffset, uRow,  pxlSrc);
		}

		pxlOldLeft = pxlLeft;
	}

	i += iOffset;

	if (i < dst->sx) {
		gdImageSetPixel (dst, i, uRow, pxlLeft);
	}

	gdImageSetPixel (dst, iOffset, uRow, clrBack);

	i--;

	while (++i < dst->sx) {
		gdImageSetPixel (dst, i, uRow, clrBack);
	}
}