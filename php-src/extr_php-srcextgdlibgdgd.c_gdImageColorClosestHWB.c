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
struct TYPE_3__ {int colorsTotal; int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; scalar_t__* open; scalar_t__ trueColor; } ;

/* Variables and functions */
 float HWB_Diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int gdTrueColor (int,int,int) ; 

int gdImageColorClosestHWB (gdImagePtr im, int r, int g, int b)
{
	int i;
	/* long rd, gd, bd; */
	int ct = (-1);
	int first = 1;
	float mindist = 0;
	if (im->trueColor) {
		return gdTrueColor(r, g, b);
	}
	for (i = 0; i < im->colorsTotal; i++) {
		float dist;
		if (im->open[i]) {
			continue;
		}
		dist = HWB_Diff(im->red[i], im->green[i], im->blue[i], r, g, b);
		if (first || (dist < mindist)) {
			mindist = dist;
			ct = i;
			first = 0;
		}
	}
	return ct;
}