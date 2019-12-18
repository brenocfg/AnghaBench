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
typedef  double float8 ;
struct TYPE_4__ {int /*<<< orphan*/  x; int /*<<< orphan*/  y; } ;
typedef  TYPE_1__ Point ;

/* Variables and functions */
 double DBL_MAX ; 
 scalar_t__ FPeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double float8_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float8_mi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline float8
point_sl(Point *pt1, Point *pt2)
{
	if (FPeq(pt1->x, pt2->x))
		return DBL_MAX;
	if (FPeq(pt1->y, pt2->y))
		return 0.0;
	return float8_div(float8_mi(pt1->y, pt2->y), float8_mi(pt1->x, pt2->x));
}