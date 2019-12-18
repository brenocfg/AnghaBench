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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 unsigned long LSM_POLICY_CHANGE ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  ima_lsm_update_rules () ; 

int ima_lsm_policy_change(struct notifier_block *nb, unsigned long event,
			  void *lsm_data)
{
	if (event != LSM_POLICY_CHANGE)
		return NOTIFY_DONE;

	ima_lsm_update_rules();
	return NOTIFY_OK;
}