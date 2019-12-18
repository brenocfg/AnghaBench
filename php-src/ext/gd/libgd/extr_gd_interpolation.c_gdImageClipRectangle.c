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
typedef  TYPE_1__* gdRectPtr ;
typedef  int /*<<< orphan*/  gdImagePtr ;
struct TYPE_3__ {int x; int width; int y; int height; } ;

/* Variables and functions */
 int CLAMP (int,int,int) ; 
 int /*<<< orphan*/  gdImageGetClip (int /*<<< orphan*/ ,int*,int*,int*,int*) ; 

__attribute__((used)) static void gdImageClipRectangle(gdImagePtr im, gdRectPtr r)
{
	int c1x, c1y, c2x, c2y;
	int x1,y1;

	gdImageGetClip(im, &c1x, &c1y, &c2x, &c2y);
	x1 = r->x + r->width - 1;
	y1 = r->y + r->height - 1;
	r->x = CLAMP(r->x, c1x, c2x);
	r->y = CLAMP(r->y, c1y, c2y);
	r->width = CLAMP(x1, c1x, c2x) - r->x + 1;
	r->height = CLAMP(y1, c1y, c2y) - r->y + 1;
}