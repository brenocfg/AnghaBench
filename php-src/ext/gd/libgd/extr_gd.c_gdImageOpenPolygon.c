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
typedef  TYPE_1__* gdPointPtr ;
typedef  int /*<<< orphan*/  gdImagePtr ;
struct TYPE_3__ {int x; int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdImageLine (int /*<<< orphan*/ ,int,int,int,int,int) ; 

void gdImageOpenPolygon (gdImagePtr im, gdPointPtr p, int n, int c)
{
	int i;
	int lx, ly;

	if (n <= 0) {
		return;
	}

	lx = p->x;
	ly = p->y;
	for (i = 1; i < n; i++) {
		p++;
		gdImageLine(im, lx, ly, p->x, p->y, c);
		lx = p->x;
		ly = p->y;
	}
}