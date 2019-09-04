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
struct TYPE_7__ {int sy; int sx; int colorsTotal; int* open; int /*<<< orphan*/ * alpha; int /*<<< orphan*/ * green; int /*<<< orphan*/ * blue; int /*<<< orphan*/ * red; scalar_t__ trueColor; } ;

/* Variables and functions */
 int gdImageColorClosestAlpha (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gdImageGetPixel (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  gdImageSetPixel (TYPE_1__*,int,int,int) ; 

void gdImagePaletteCopy (gdImagePtr to, gdImagePtr from)
{
	int i;
	int x, y, p;
	int xlate[256];
	if (to->trueColor || from->trueColor) {
		return;
	}

	for (i = 0; i < 256; i++) {
		xlate[i] = -1;
	}

	for (y = 0; y < to->sy; y++) {
		for (x = 0; x < to->sx; x++) {
			p = gdImageGetPixel(to, x, y);
			if (xlate[p] == -1) {
				/* This ought to use HWB, but we don't have an alpha-aware version of that yet. */
				xlate[p] = gdImageColorClosestAlpha (from, to->red[p], to->green[p], to->blue[p], to->alpha[p]);
			}
			gdImageSetPixel(to, x, y, xlate[p]);
		}
	}

	for (i = 0; i < from->colorsTotal; i++) {
		to->red[i] = from->red[i];
		to->blue[i] = from->blue[i];
		to->green[i] = from->green[i];
		to->alpha[i] = from->alpha[i];
		to->open[i] = 0;
	}

	for (i = from->colorsTotal; i < to->colorsTotal; i++) {
		to->open[i] = 1;
	}

	to->colorsTotal = from->colorsTotal;
}