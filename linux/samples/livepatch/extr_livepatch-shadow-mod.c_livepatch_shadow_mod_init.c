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
 int ALLOC_PERIOD ; 
 int CLEANUP_PERIOD ; 
 int /*<<< orphan*/  alloc_dwork ; 
 int /*<<< orphan*/  cleanup_dwork ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int livepatch_shadow_mod_init(void)
{
	schedule_delayed_work(&alloc_dwork,
		msecs_to_jiffies(1000 * ALLOC_PERIOD));
	schedule_delayed_work(&cleanup_dwork,
		msecs_to_jiffies(1000 * CLEANUP_PERIOD));

	return 0;
}