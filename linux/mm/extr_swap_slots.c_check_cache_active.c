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
 long THRESHOLD_ACTIVATE_SWAP_SLOTS_CACHE ; 
 long THRESHOLD_DEACTIVATE_SWAP_SLOTS_CACHE ; 
 int /*<<< orphan*/  deactivate_swap_slots_cache () ; 
 long get_nr_swap_pages () ; 
 long num_online_cpus () ; 
 int /*<<< orphan*/  reactivate_swap_slots_cache () ; 
 int swap_slot_cache_active ; 
 int /*<<< orphan*/  swap_slot_cache_enabled ; 
 int /*<<< orphan*/  swap_slot_cache_initialized ; 

__attribute__((used)) static bool check_cache_active(void)
{
	long pages;

	if (!swap_slot_cache_enabled || !swap_slot_cache_initialized)
		return false;

	pages = get_nr_swap_pages();
	if (!swap_slot_cache_active) {
		if (pages > num_online_cpus() *
		    THRESHOLD_ACTIVATE_SWAP_SLOTS_CACHE)
			reactivate_swap_slots_cache();
		goto out;
	}

	/* if global pool of slot caches too low, deactivate cache */
	if (pages < num_online_cpus() * THRESHOLD_DEACTIVATE_SWAP_SLOTS_CACHE)
		deactivate_swap_slots_cache();
out:
	return swap_slot_cache_active;
}