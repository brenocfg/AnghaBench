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
struct kobject {int dummy; } ;
struct attribute {int dummy; } ;

/* Variables and functions */
 int sysfs_create_file (struct kobject*,struct attribute const* const) ; 
 int /*<<< orphan*/  sysfs_remove_file (struct kobject*,struct attribute const* const) ; 

int sysfs_create_files(struct kobject *kobj, const struct attribute * const *ptr)
{
	int err = 0;
	int i;

	for (i = 0; ptr[i] && !err; i++)
		err = sysfs_create_file(kobj, ptr[i]);
	if (err)
		while (--i >= 0)
			sysfs_remove_file(kobj, ptr[i]);
	return err;
}