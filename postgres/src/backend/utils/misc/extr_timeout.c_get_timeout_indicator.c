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
typedef  size_t TimeoutId ;
struct TYPE_2__ {int indicator; } ;

/* Variables and functions */
 TYPE_1__* all_timeouts ; 

bool
get_timeout_indicator(TimeoutId id, bool reset_indicator)
{
	if (all_timeouts[id].indicator)
	{
		if (reset_indicator)
			all_timeouts[id].indicator = false;
		return true;
	}
	return false;
}