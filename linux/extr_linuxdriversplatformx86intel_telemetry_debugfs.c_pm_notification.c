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
 int NOTIFY_DONE ; 
#define  PM_POST_SUSPEND 129 
#define  PM_SUSPEND_PREPARE 128 
 int pm_suspend_exit_cb () ; 
 int pm_suspend_prep_cb () ; 

__attribute__((used)) static int pm_notification(struct notifier_block *this,
			   unsigned long event, void *ptr)
{
	switch (event) {
	case PM_SUSPEND_PREPARE:
		return pm_suspend_prep_cb();
	case PM_POST_SUSPEND:
		return pm_suspend_exit_cb();
	}

	return NOTIFY_DONE;
}