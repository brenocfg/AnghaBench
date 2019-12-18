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
struct TYPE_10__ {int* tileColorMap; int /*<<< orphan*/  trueColor; struct TYPE_10__* tile; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdImageAlpha (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gdImageBlue (TYPE_1__*,int) ; 
 int gdImageColorResolveAlpha (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gdImageColorsTotal (TYPE_1__*) ; 
 int /*<<< orphan*/  gdImageGreen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gdImageRed (TYPE_1__*,int) ; 

void gdImageSetTile (gdImagePtr im, gdImagePtr tile)
{
	int i;
	im->tile = tile;
	if (!im->trueColor && !im->tile->trueColor) {
		for (i = 0; i < gdImageColorsTotal(tile); i++) {
			int index;
			index = gdImageColorResolveAlpha(im, gdImageRed(tile, i), gdImageGreen(tile, i), gdImageBlue(tile, i), gdImageAlpha(tile, i));
			im->tileColorMap[i] = index;
		}
	}
}