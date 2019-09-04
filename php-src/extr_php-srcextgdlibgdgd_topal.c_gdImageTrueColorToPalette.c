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
typedef  int /*<<< orphan*/  gdImagePtr ;

/* Variables and functions */
 int gdImageTrueColorToPaletteBody (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int gdImageTrueColorToPalette (gdImagePtr im, int dither, int colorsWanted)
{
	return gdImageTrueColorToPaletteBody(im, dither, colorsWanted, 0);
}