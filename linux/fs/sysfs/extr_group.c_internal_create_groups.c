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
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int internal_create_group (struct kobject*,int,struct attribute_group const*) ; 
 int /*<<< orphan*/  sysfs_remove_group (struct kobject*,struct attribute_group const*) ; 

__attribute__((used)) static int internal_create_groups(struct kobject *kobj, int update,
				  const struct attribute_group **groups)
{
	int error = 0;
	int i;

	if (!groups)
		return 0;

	for (i = 0; groups[i]; i++) {
		error = internal_create_group(kobj, update, groups[i]);
		if (error) {
			while (--i >= 0)
				sysfs_remove_group(kobj, groups[i]);
			break;
		}
	}
	return error;
}