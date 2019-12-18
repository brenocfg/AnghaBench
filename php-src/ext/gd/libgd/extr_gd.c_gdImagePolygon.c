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
typedef  TYPE_1__* gdPointPtr ;
typedef  int /*<<< orphan*/  gdImagePtr ;
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdImageLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gdImageOpenPolygon (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 

void gdImagePolygon (gdImagePtr im, gdPointPtr p, int n, int c)
{
	if (n <= 0) {
		return;
	}


	gdImageLine (im, p->x, p->y, p[n - 1].x, p[n - 1].y, c);
	gdImageOpenPolygon (im, p, n, c);
}