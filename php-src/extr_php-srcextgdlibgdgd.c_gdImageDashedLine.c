#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_4__ {int thick; } ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  atan2 (int,int) ; 
 int /*<<< orphan*/  dashedSet (TYPE_1__*,int,int,int,int*,int*,int,int) ; 
 double sin (int /*<<< orphan*/ ) ; 

void gdImageDashedLine (gdImagePtr im, int x1, int y1, int x2, int y2, int color)
{
	int dx, dy, incr1, incr2, d, x, y, xend, yend, xdirflag, ydirflag;
	int dashStep = 0;
	int on = 1;
	int wid;
	int vert;
	int thick = im->thick;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	if (dy <= dx) {
		/* More-or-less horizontal. use wid for vertical stroke */
		/* 2.0.12: Michael Schwartz: divide rather than multiply;
		TBB: but watch out for /0! */
		double as = sin(atan2(dy, dx));
		if (as != 0) {
			wid = thick / as;
		} else {
			wid = 1;
		}
		vert = 1;

		d = 2 * dy - dx;
		incr1 = 2 * dy;
		incr2 = 2 * (dy - dx);
		if (x1 > x2) {
			x = x2;
			y = y2;
			ydirflag = (-1);
			xend = x1;
		} else {
			x = x1;
			y = y1;
			ydirflag = 1;
			xend = x2;
		}
		dashedSet(im, x, y, color, &on, &dashStep, wid, vert);
		if (((y2 - y1) * ydirflag) > 0) {
			while (x < xend) {
				x++;
				if (d < 0) {
					d += incr1;
				} else {
					y++;
					d += incr2;
				}
				dashedSet(im, x, y, color, &on, &dashStep, wid, vert);
			}
		} else {
			while (x < xend) {
				x++;
				if (d < 0) {
					d += incr1;
				} else {
					y--;
					d += incr2;
				}
				dashedSet(im, x, y, color, &on, &dashStep, wid, vert);
			}
		}
	} else {
		/* 2.0.12: Michael Schwartz: divide rather than multiply;
		TBB: but watch out for /0! */
		double as = sin (atan2 (dy, dx));
		if (as != 0) {
			wid = thick / as;
		} else {
			wid = 1;
		}
		vert = 0;

		d = 2 * dx - dy;
		incr1 = 2 * dx;
		incr2 = 2 * (dx - dy);
		if (y1 > y2) {
			y = y2;
			x = x2;
			yend = y1;
			xdirflag = (-1);
		} else {
			y = y1;
			x = x1;
			yend = y2;
			xdirflag = 1;
		}
		dashedSet(im, x, y, color, &on, &dashStep, wid, vert);
		if (((x2 - x1) * xdirflag) > 0) {
			while (y < yend) {
				y++;
				if (d < 0) {
					d += incr1;
				} else {
					x++;
					d += incr2;
				}
				dashedSet(im, x, y, color, &on, &dashStep, wid, vert);
			}
		} else {
			while (y < yend) {
				y++;
				if (d < 0) {
					d += incr1;
				} else {
					x--;
					d += incr2;
				}
				dashedSet(im, x, y, color, &on, &dashStep, wid, vert);
			}
		}
	}
}