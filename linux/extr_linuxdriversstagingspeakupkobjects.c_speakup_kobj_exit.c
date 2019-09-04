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
 int /*<<< orphan*/  accessibility_kobj ; 
 int /*<<< orphan*/  i18n_attr_group ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_attr_group ; 
 int /*<<< orphan*/  speakup_kobj ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void speakup_kobj_exit(void)
{
	sysfs_remove_group(speakup_kobj, &i18n_attr_group);
	sysfs_remove_group(speakup_kobj, &main_attr_group);
	kobject_put(speakup_kobj);
	kobject_put(accessibility_kobj);
}