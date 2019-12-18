#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  gs_timer_range_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 

bool gs_timer_range_get_data(gs_timer_range_t *range, bool *disjoint,
			     uint64_t *frequency)
{
	UNUSED_PARAMETER(range);

	*disjoint = false;
	*frequency = 1000000000;
	return true;
}