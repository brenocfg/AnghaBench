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
struct user_namespace {int dummy; } ;

/* Variables and functions */

bool setup_userns_sysctls(struct user_namespace *ns)
{
#ifdef CONFIG_SYSCTL
	struct ctl_table *tbl;
	setup_sysctl_set(&ns->set, &set_root, set_is_seen);
	tbl = kmemdup(user_table, sizeof(user_table), GFP_KERNEL);
	if (tbl) {
		int i;
		for (i = 0; i < UCOUNT_COUNTS; i++) {
			tbl[i].data = &ns->ucount_max[i];
		}
		ns->sysctls = __register_sysctl_table(&ns->set, "user", tbl);
	}
	if (!ns->sysctls) {
		kfree(tbl);
		retire_sysctl_set(&ns->set);
		return false;
	}
#endif
	return true;
}