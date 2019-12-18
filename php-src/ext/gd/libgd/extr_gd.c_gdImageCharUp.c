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
typedef  int /*<<< orphan*/  gdImagePtr ;
typedef  TYPE_1__* gdFontPtr ;
struct TYPE_3__ {int offset; int nchars; int h; int w; scalar_t__* data; } ;

/* Variables and functions */
 int ASC (int) ; 
 int /*<<< orphan*/  gdImageSetPixel (int /*<<< orphan*/ ,int,int,int) ; 

void gdImageCharUp (gdImagePtr im, gdFontPtr f, int x, int y, int c, int color)
{
	int cx, cy;
	int px, py;
	int fline;
	cx = 0;
	cy = 0;
#ifdef CHARSET_EBCDIC
	c = ASC (c);
#endif /*CHARSET_EBCDIC */
	if ((c < f->offset) || (c >= (f->offset + f->nchars))) {
		return;
	}
	fline = (c - f->offset) * f->h * f->w;
	for (py = y; py > (y - f->w); py--) {
		for (px = x; px < (x + f->h); px++) {
			if (f->data[fline + cy * f->w + cx]) {
				gdImageSetPixel(im, px, py, color);
			}
			cy++;
		}
		cy = 0;
		cx++;
	}
}