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
struct TYPE_4__ {int** tpixels; int const transparent; int const cy1; size_t cx1; int const cy2; int const cx2; } ;

/* Variables and functions */
 scalar_t__ gdImageBoundsSafe (TYPE_1__*,int const,int const) ; 
 int gdTrueColorAlpha (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gdTrueColorGetBlue (int) ; 
 int /*<<< orphan*/  gdTrueColorGetGreen (int) ; 
 int /*<<< orphan*/  gdTrueColorGetRed (int) ; 

__attribute__((used)) static inline int getPixelOverflowColorTC(gdImagePtr im, const int x, const int y, const int color)
{
	if (gdImageBoundsSafe(im, x, y)) {
		const int c = im->tpixels[y][x];
		if (c == im->transparent) {
			return gdTrueColorAlpha(0, 0, 0, 127);
		}
		return c;
	} else {
		register int border = 0;
		if (y < im->cy1) {
			border = im->tpixels[0][im->cx1];
			goto processborder;
		}

		if (y < im->cy1) {
			border = im->tpixels[0][im->cx1];
			goto processborder;
		}

		if (y > im->cy2) {
			if (x >= im->cx1 && x <= im->cx1) {
				border = im->tpixels[im->cy2][x];
				goto processborder;
			} else {
				return gdTrueColorAlpha(0, 0, 0, 127);
			}
		}

		/* y is bound safe at this point */
		if (x < im->cx1) {
			border = im->tpixels[y][im->cx1];
			goto processborder;
		}

		if (x > im->cx2) {
			border = im->tpixels[y][im->cx2];
		}

processborder:
		if (border == im->transparent) {
			return gdTrueColorAlpha(0, 0, 0, 127);
		} else{
			return gdTrueColorAlpha(gdTrueColorGetRed(border), gdTrueColorGetGreen(border), gdTrueColorGetBlue(border), 127);
		}
	}
}