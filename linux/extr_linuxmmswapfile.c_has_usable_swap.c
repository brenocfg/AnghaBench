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
 scalar_t__ plist_head_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_active_head ; 
 int /*<<< orphan*/  swap_lock ; 

bool has_usable_swap(void)
{
	bool ret = true;

	spin_lock(&swap_lock);
	if (plist_head_empty(&swap_active_head))
		ret = false;
	spin_unlock(&swap_lock);
	return ret;
}