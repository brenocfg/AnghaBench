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

void exofs_sysfs_dbg_print(void)
{
#ifdef CONFIG_EXOFS_DEBUG
	struct kobject *k_name, *k_tmp;

	list_for_each_entry_safe(k_name, k_tmp, &exofs_kset->list, entry) {
		printk(KERN_INFO "%s: name %s ref %d\n",
			__func__, kobject_name(k_name),
			(int)kref_read(&k_name->kref));
	}
#endif
}