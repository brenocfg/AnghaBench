#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cost; } ;
typedef  TYPE_1__ SPLITCOST ;

/* Variables and functions */

__attribute__((used)) static int
comparecost(const void *va, const void *vb)
{
	const SPLITCOST *a = (const SPLITCOST *) va;
	const SPLITCOST *b = (const SPLITCOST *) vb;

	if (a->cost == b->cost)
		return 0;
	else
		return (a->cost > b->cost) ? 1 : -1;
}