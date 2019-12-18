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
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_3__ {int sx; int sy; int cx1; int cy1; int cx2; int cy2; } ;

/* Variables and functions */

void gdImageSetClip (gdImagePtr im, int x1, int y1, int x2, int y2)
{
	if (x1 < 0) {
		x1 = 0;
	}
	if (x1 >= im->sx) {
		x1 = im->sx - 1;
	}
	if (x2 < 0) {
		x2 = 0;
	}
	if (x2 >= im->sx) {
		x2 = im->sx - 1;
	}
	if (y1 < 0) {
		y1 = 0;
	}
	if (y1 >= im->sy) {
		y1 = im->sy - 1;
	}
	if (y2 < 0) {
		y2 = 0;
	}
	if (y2 >= im->sy) {
		y2 = im->sy - 1;
	}
	im->cx1 = x1;
	im->cy1 = y1;
	im->cx2 = x2;
	im->cy2 = y2;
}