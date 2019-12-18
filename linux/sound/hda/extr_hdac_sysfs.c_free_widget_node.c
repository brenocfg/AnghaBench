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
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  sysfs_remove_group (struct kobject*,struct attribute_group const*) ; 

__attribute__((used)) static void free_widget_node(struct kobject *kobj,
			     const struct attribute_group *group)
{
	if (kobj) {
		sysfs_remove_group(kobj, group);
		kobject_put(kobj);
	}
}