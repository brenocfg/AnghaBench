#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_10__ {int* brushColorMap; int /*<<< orphan*/  trueColor; struct TYPE_10__* brush; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdImageAlpha (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gdImageBlue (TYPE_1__*,int) ; 
 int gdImageColorResolveAlpha (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gdImageColorsTotal (TYPE_1__*) ; 
 int /*<<< orphan*/  gdImageGreen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gdImageRed (TYPE_1__*,int) ; 

void gdImageSetBrush (gdImagePtr im, gdImagePtr brush)
{
	int i;
	im->brush = brush;
	if (!im->trueColor && !im->brush->trueColor) {
		for (i = 0; i < gdImageColorsTotal(brush); i++) {
			int index;
			index = gdImageColorResolveAlpha(im, gdImageRed(brush, i), gdImageGreen(brush, i), gdImageBlue(brush, i), gdImageAlpha(brush, i));
			im->brushColorMap[i] = index;
		}
	}
}