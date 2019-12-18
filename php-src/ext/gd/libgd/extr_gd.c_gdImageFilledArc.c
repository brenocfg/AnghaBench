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
struct TYPE_3__ {int x; int y; } ;
typedef  TYPE_1__ gdPoint ;
typedef  int /*<<< orphan*/  gdImagePtr ;

/* Variables and functions */
 int gdChord ; 
 scalar_t__* gdCosT ; 
 int gdEdged ; 
 int /*<<< orphan*/  gdImageFilledPolygon (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  gdImageLine (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int gdNoFill ; 
 scalar_t__* gdSinT ; 

void gdImageFilledArc (gdImagePtr im, int cx, int cy, int w, int h, int s, int e, int color, int style)
{
	gdPoint pts[363];
	int i, pti;
	int lx = 0, ly = 0;
	int fx = 0, fy = 0;
	int startx = -1, starty = -1, endx = -1, endy = -1;

    if ((s % 360)  == (e % 360)) {
		s = 0; e = 360;
	} else {
		if (s > 360) {
			s = s % 360;
		}

		if (e > 360) {
			e = e % 360;
		}

		while (s < 0) {
			s += 360;
		}

		while (e < s) {
			e += 360;
		}
		if (s == e) {
			s = 0; e = 360;
		}
	}

	for (i = s, pti = 1; i <= e; i++, pti++) {
		int x, y;
		x = endx = ((long) gdCosT[i % 360] * (long) w / (2 * 1024)) + cx;
		y = endy = ((long) gdSinT[i % 360] * (long) h / (2 * 1024)) + cy;
		if (i != s) {
			if (!(style & gdChord)) {
				if (style & gdNoFill) {
					gdImageLine(im, lx, ly, x, y, color);
				} else {
					if (y == ly) {
						pti--; /* don't add this point */
						if (((i > 270 || i < 90) && x > lx) || ((i >  90 && i < 270) && x < lx)) {
							/* replace the old x coord, if increasing on the
							   right side or decreasing on the left side */
							pts[pti].x = x;
						}
					} else {
						pts[pti].x = x;
						pts[pti].y = y;
					}
  				}
			}
		} else {
			fx = x;
			fy = y;
			if (!(style & (gdChord | gdNoFill))) {
				pts[0].x = cx;
				pts[0].y = cy;
				pts[pti].x = startx = x;
				pts[pti].y = starty = y;
			}
		}
		lx = x;
		ly = y;
	}
	if (style & gdChord) {
		if (style & gdNoFill) {
			if (style & gdEdged) {
				gdImageLine(im, cx, cy, lx, ly, color);
				gdImageLine(im, cx, cy, fx, fy, color);
			}
			gdImageLine(im, fx, fy, lx, ly, color);
		} else {
			pts[0].x = fx;
			pts[0].y = fy;
			pts[1].x = lx;
			pts[1].y = ly;
			pts[2].x = cx;
			pts[2].y = cy;
			gdImageFilledPolygon(im, pts, 3, color);
		}
	} else {
		if (style & gdNoFill) {
			if (style & gdEdged) {
				gdImageLine(im, cx, cy, lx, ly, color);
				gdImageLine(im, cx, cy, fx, fy, color);
			}
		} else {
			if (e - s < 360) {
				if (pts[1].x != startx && pts[1].y == starty) {
					/* start point has been removed due to y-coord fix => insert it */
					for (i = pti; i > 1; i--) {
						pts[i].x = pts[i-1].x;
						pts[i].y = pts[i-1].y;
					}
					pts[1].x = startx;
					pts[1].y = starty;
					pti++;
				}
				if (pts[pti-1].x != endx && pts[pti-1].y == endy) {
					/* end point has been removed due to y-coord fix => insert it */
					pts[pti].x = endx;
					pts[pti].y = endy;
					pti++;
				}
			}
			pts[pti].x = cx;
			pts[pti].y = cy;
			gdImageFilledPolygon(im, pts, pti+1, color);
		}
	}
}