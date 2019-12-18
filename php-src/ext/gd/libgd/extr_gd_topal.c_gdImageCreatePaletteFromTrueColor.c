#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * gdImagePtr ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 scalar_t__ gdImageTrueColorToPaletteBody (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 

gdImagePtr gdImageCreatePaletteFromTrueColor (gdImagePtr im, int dither, int colorsWanted)
{
	gdImagePtr nim;
	if (TRUE == gdImageTrueColorToPaletteBody(im, dither, colorsWanted, &nim)) {
		return nim;
	}
	return NULL;
}