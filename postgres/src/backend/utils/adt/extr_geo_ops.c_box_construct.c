#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_11__ {TYPE_2__ low; TYPE_1__ high; } ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ Point ;
typedef  TYPE_4__ BOX ;

/* Variables and functions */
 scalar_t__ float8_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
box_construct(BOX *result, Point *pt1, Point *pt2)
{
	if (float8_gt(pt1->x, pt2->x))
	{
		result->high.x = pt1->x;
		result->low.x = pt2->x;
	}
	else
	{
		result->high.x = pt2->x;
		result->low.x = pt1->x;
	}
	if (float8_gt(pt1->y, pt2->y))
	{
		result->high.y = pt1->y;
		result->low.y = pt2->y;
	}
	else
	{
		result->high.y = pt2->y;
		result->low.y = pt1->y;
	}
}