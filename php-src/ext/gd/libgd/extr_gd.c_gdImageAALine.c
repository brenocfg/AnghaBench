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
struct TYPE_7__ {long sy; long sx; int /*<<< orphan*/  trueColor; } ;

/* Variables and functions */
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  clip_1d (int*,int*,int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  gdImageLine (TYPE_1__*,int,int,int,int,int) ; 
 scalar_t__ gdImageSX (TYPE_1__*) ; 
 scalar_t__ gdImageSY (TYPE_1__*) ; 
 int /*<<< orphan*/  gdImageSetAAPixelColor (TYPE_1__*,long,long,int,long) ; 

void gdImageAALine (gdImagePtr im, int x1, int y1, int x2, int y2, int col)
{
	/* keep them as 32bits */
	long x, y, inc, frac;
	long dx, dy,tmp;

	if (!im->trueColor) {
		/* TBB: don't crash when the image is of the wrong type */
		gdImageLine(im, x1, y1, x2, y2, col);
		return;
	}

	/* 2.0.10: Nick Atty: clip to edges of drawing rectangle, return if no points need to be drawn */
	if (!clip_1d(&x1,&y1,&x2,&y2,gdImageSX(im)-1) || !clip_1d(&y1,&x1,&y2,&x2,gdImageSY(im)-1)) {
		return;
	}

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx == 0 && dy == 0) {
		return;
	}
	if (abs((int)dx) > abs((int)dy)) {
		if (dx < 0) {
			tmp = x1;
			x1 = x2;
			x2 = tmp;
			tmp = y1;
			y1 = y2;
			y2 = tmp;
			dx = x2 - x1;
			dy = y2 - y1;
		}
		y = y1;
		inc = (dy * 65536) / dx;
		frac = 0;
		for (x = x1; x <= x2; x++) {
			gdImageSetAAPixelColor(im, x, y, col, (frac >> 8) & 0xFF);
			if (y + 1 < im->sy) {
				gdImageSetAAPixelColor(im, x, y + 1, col, (~frac >> 8) & 0xFF);
			}
			frac += inc;
			if (frac >= 65536) {
				frac -= 65536;
				y++;
			} else if (frac < 0) {
				frac += 65536;
				y--;
			}
		}
	} else {
		if (dy < 0) {
			tmp = x1;
			x1 = x2;
			x2 = tmp;
			tmp = y1;
			y1 = y2;
			y2 = tmp;
			dx = x2 - x1;
			dy = y2 - y1;
		}
		x = x1;
		inc = (dx * 65536) / dy;
		frac = 0;
		for (y = y1; y <= y2; y++) {
			gdImageSetAAPixelColor(im, x, y, col, (frac >> 8) & 0xFF);
			if (x + 1 < im->sx) {
				gdImageSetAAPixelColor(im, x + 1, y, col, (~frac >> 8) & 0xFF);
			}
			frac += inc;
			if (frac >= 65536) {
				frac -= 65536;
				x++;
			} else if (frac < 0) {
				frac += 65536;
				x--;
			}
		}
	}
}