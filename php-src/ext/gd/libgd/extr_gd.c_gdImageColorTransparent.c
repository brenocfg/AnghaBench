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
struct TYPE_3__ {int colorsTotal; int transparent; int /*<<< orphan*/ * alpha; int /*<<< orphan*/  trueColor; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdAlphaOpaque ; 
 int /*<<< orphan*/  gdAlphaTransparent ; 

void gdImageColorTransparent (gdImagePtr im, int color)
{
	if (color < 0) {
		return;
	}
	if (!im->trueColor) {
		if((color >= im->colorsTotal)) {
			return;
		}
		/* Make the old transparent color opaque again */
		if (im->transparent != -1) {
			im->alpha[im->transparent] = gdAlphaOpaque;
		}
		im->alpha[color] = gdAlphaTransparent;
	}
	im->transparent = color;
}