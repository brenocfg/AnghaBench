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
struct TYPE_11__ {int sy; int transparent; scalar_t__ trueColor; } ;
typedef  int (* FuncPtr ) (gdImagePtr,int,int) ;

/* Variables and functions */
 int gdImageAlpha (TYPE_1__*,int) ; 
 int gdImageBlue (TYPE_1__*,int) ; 
 int gdImageColorAllocateAlpha (TYPE_1__*,int,int,int,int) ; 
 int gdImageColorClosestAlpha (TYPE_1__*,int,int,int,int) ; 
 int gdImageGetPixel (gdImagePtr,int,int) ; 
 int gdImageGetTrueColorPixel (gdImagePtr,int,int) ; 
 int gdImageGreen (TYPE_1__*,int) ; 
 int gdImageRed (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gdImageSetPixel (TYPE_1__*,int,int,int) ; 

void gdImageSkewY (gdImagePtr dst, gdImagePtr src, int uCol, int iOffset, double dWeight, int clrBack, int ignoretransparent)
{
	typedef int (*FuncPtr)(gdImagePtr, int, int);
	int i, iYPos=0, r, g, b, a;
	FuncPtr f;
	int pxlOldLeft, pxlLeft=0, pxlSrc;

	if (src->trueColor) {
		f = gdImageGetTrueColorPixel;
	} else {
		f = gdImageGetPixel;
	}

	for (i = 0; i<=iOffset; i++) {
		gdImageSetPixel (dst, uCol, i, clrBack);
	}
	r = (int)((double)gdImageRed(src,clrBack) * dWeight);
	g = (int)((double)gdImageGreen(src,clrBack) * dWeight);
	b = (int)((double)gdImageBlue(src,clrBack) * dWeight);
	a = (int)((double)gdImageAlpha(src,clrBack) * dWeight);

	pxlOldLeft = gdImageColorAllocateAlpha(dst, r, g, b, a);

	for (i = 0; i < src->sy; i++) {
		pxlSrc = f (src, uCol, i);
		iYPos = i + iOffset;

		r = (int)((double)gdImageRed(src,pxlSrc) * dWeight);
		g = (int)((double)gdImageGreen(src,pxlSrc) * dWeight);
		b = (int)((double)gdImageBlue(src,pxlSrc) * dWeight);
		a = (int)((double)gdImageAlpha(src,pxlSrc) * dWeight);

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

		if ((iYPos >= 0) && (iYPos < dst->sy)) {
			gdImageSetPixel (dst, uCol, iYPos, pxlSrc);
		}

		pxlOldLeft = pxlLeft;
	}

	i = iYPos;
	if (i < dst->sy) {
		gdImageSetPixel (dst, uCol, i, pxlLeft);
	}

	i--;
	while (++i < dst->sy) {
		gdImageSetPixel (dst, uCol, i, clrBack);
	}
}