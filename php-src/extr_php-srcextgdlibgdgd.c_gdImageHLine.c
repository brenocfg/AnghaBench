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
struct TYPE_5__ {int thick; } ;

/* Variables and functions */
 int /*<<< orphan*/  _gdImageFilledHRectangle (TYPE_1__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  gdImageSetPixel (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static void gdImageHLine(gdImagePtr im, int y, int x1, int x2, int col)
{
	if (im->thick > 1) {
		int thickhalf = im->thick >> 1;
		_gdImageFilledHRectangle(im, x1, y - thickhalf, x2, y + im->thick - thickhalf - 1, col);
	} else {
		if (x2 < x1) {
			int t = x2;
			x2 = x1;
			x1 = t;
		}

		for (;x1 <= x2; x1++) {
			gdImageSetPixel(im, x1, y, col);
		}
	}
	return;
}