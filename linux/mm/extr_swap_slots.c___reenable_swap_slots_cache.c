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
 int /*<<< orphan*/  has_usable_swap () ; 
 int /*<<< orphan*/  swap_slot_cache_enabled ; 

__attribute__((used)) static void __reenable_swap_slots_cache(void)
{
	swap_slot_cache_enabled = has_usable_swap();
}