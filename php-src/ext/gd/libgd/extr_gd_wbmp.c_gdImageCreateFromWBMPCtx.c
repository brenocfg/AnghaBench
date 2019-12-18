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
typedef  int /*<<< orphan*/ * gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_4__ {int width; int height; scalar_t__* bitmap; } ;
typedef  TYPE_1__ Wbmp ;

/* Variables and functions */
 scalar_t__ WBMP_WHITE ; 
 int /*<<< orphan*/  freewbmp (TYPE_1__*) ; 
 int gdImageColorAllocate (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * gdImageCreate (int,int) ; 
 int /*<<< orphan*/  gdImageSetPixel (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  gd_getin ; 
 scalar_t__ readwbmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 

gdImagePtr gdImageCreateFromWBMPCtx (gdIOCtx * infile)
{
	/* FILE *wbmp_file; */
	Wbmp *wbmp;
	gdImagePtr im = NULL;
	int black, white;
	int col, row, pos;

	if (readwbmp (&gd_getin, infile, &wbmp)) {
		return NULL;
	}

	if (!(im = gdImageCreate (wbmp->width, wbmp->height))) {
		freewbmp (wbmp);
		return NULL;
	}

	/* create the background color */
	white = gdImageColorAllocate(im, 255, 255, 255);
	/* create foreground color */
	black = gdImageColorAllocate(im, 0, 0, 0);

	/* fill in image (in a wbmp 1 = white/ 0 = black) */
	pos = 0;
	for (row = 0; row < wbmp->height; row++) {
		for (col = 0; col < wbmp->width; col++) {
			if (wbmp->bitmap[pos++] == WBMP_WHITE) {
				gdImageSetPixel(im, col, row, white);
			} else {
				gdImageSetPixel(im, col, row, black);
			}
		}
	}

	freewbmp(wbmp);

	return im;
}