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

/* Variables and functions */
 int /*<<< orphan*/  __reenable_swap_slots_cache () ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_slots_cache_enable_mutex ; 

void reenable_swap_slots_cache_unlock(void)
{
	__reenable_swap_slots_cache();
	mutex_unlock(&swap_slots_cache_enable_mutex);
}