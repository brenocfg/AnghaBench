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
 int SLOTS_CACHE ; 
 int SLOTS_CACHE_RET ; 
 int /*<<< orphan*/  __drain_swap_slots_cache (int) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int swap_slot_cache_enabled ; 
 scalar_t__ swap_slot_cache_initialized ; 
 int /*<<< orphan*/  swap_slots_cache_enable_mutex ; 

void disable_swap_slots_cache_lock(void)
{
	mutex_lock(&swap_slots_cache_enable_mutex);
	swap_slot_cache_enabled = false;
	if (swap_slot_cache_initialized) {
		/* serialize with cpu hotplug operations */
		get_online_cpus();
		__drain_swap_slots_cache(SLOTS_CACHE|SLOTS_CACHE_RET);
		put_online_cpus();
	}
}