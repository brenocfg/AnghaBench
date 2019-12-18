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
struct TYPE_2__ {double delta; } ;
typedef  TYPE_1__ CommonEntry ;

/* Variables and functions */

__attribute__((used)) static int
common_entry_cmp(const void *i1, const void *i2)
{
	double		delta1 = ((CommonEntry *) i1)->delta;
	double		delta2 = ((CommonEntry *) i2)->delta;

	if (delta1 < delta2)
		return -1;
	else if (delta1 > delta2)
		return 1;
	else
		return 0;
}