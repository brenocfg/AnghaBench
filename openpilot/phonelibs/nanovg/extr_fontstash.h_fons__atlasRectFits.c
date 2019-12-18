#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int width; int nnodes; int height; TYPE_1__* nodes; } ;
struct TYPE_4__ {int x; int y; scalar_t__ width; } ;
typedef  TYPE_2__ FONSatlas ;

/* Variables and functions */
 int fons__maxi (int,int) ; 

__attribute__((used)) static int fons__atlasRectFits(FONSatlas* atlas, int i, int w, int h)
{
	// Checks if there is enough space at the location of skyline span 'i',
	// and return the max height of all skyline spans under that at that location,
	// (think tetris block being dropped at that position). Or -1 if no space found.
	int x = atlas->nodes[i].x;
	int y = atlas->nodes[i].y;
	int spaceLeft;
	if (x + w > atlas->width)
		return -1;
	spaceLeft = w;
	while (spaceLeft > 0) {
		if (i == atlas->nnodes) return -1;
		y = fons__maxi(y, atlas->nodes[i].y);
		if (y + h > atlas->height) return -1;
		spaceLeft -= atlas->nodes[i].width;
		++i;
	}
	return y;
}