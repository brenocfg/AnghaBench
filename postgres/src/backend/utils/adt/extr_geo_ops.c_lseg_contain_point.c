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
struct TYPE_3__ {int /*<<< orphan*/ * p; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  TYPE_1__ LSEG ;

/* Variables and functions */
 int FPeq (scalar_t__,scalar_t__) ; 
 scalar_t__ point_dt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
lseg_contain_point(LSEG *lseg, Point *pt)
{
	return FPeq(point_dt(pt, &lseg->p[0]) +
				point_dt(pt, &lseg->p[1]),
				point_dt(&lseg->p[0], &lseg->p[1]));
}