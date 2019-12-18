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
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ Point ;

/* Variables and functions */
 scalar_t__ FPeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ float8_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
point_eq_point(Point *pt1, Point *pt2)
{
	return ((FPeq(pt1->x, pt2->x) && FPeq(pt1->y, pt2->y)) ||
			(float8_eq(pt1->x, pt2->x) && float8_eq(pt1->y, pt2->y)));
}