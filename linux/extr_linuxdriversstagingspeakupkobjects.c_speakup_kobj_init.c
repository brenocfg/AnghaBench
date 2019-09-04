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
 int ENOMEM ; 
 int /*<<< orphan*/ * accessibility_kobj ; 
 int /*<<< orphan*/  i18n_attr_group ; 
 int /*<<< orphan*/ * kobject_create_and_add (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_attr_group ; 
 int /*<<< orphan*/ * speakup_kobj ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int speakup_kobj_init(void)
{
	int retval;

	/*
	 * Create a simple kobject with the name of "accessibility",
	 * located under /sys/
	 *
	 * As this is a simple directory, no uevent will be sent to
	 * userspace.  That is why this function should not be used for
	 * any type of dynamic kobjects, where the name and number are
	 * not known ahead of time.
	 */
	accessibility_kobj = kobject_create_and_add("accessibility", NULL);
	if (!accessibility_kobj) {
		retval = -ENOMEM;
		goto out;
	}

	speakup_kobj = kobject_create_and_add("speakup", accessibility_kobj);
	if (!speakup_kobj) {
		retval = -ENOMEM;
		goto err_acc;
	}

	/* Create the files associated with this kobject */
	retval = sysfs_create_group(speakup_kobj, &main_attr_group);
	if (retval)
		goto err_speakup;

	retval = sysfs_create_group(speakup_kobj, &i18n_attr_group);
	if (retval)
		goto err_group;

	goto out;

err_group:
	sysfs_remove_group(speakup_kobj, &main_attr_group);
err_speakup:
	kobject_put(speakup_kobj);
err_acc:
	kobject_put(accessibility_kobj);
out:
	return retval;
}