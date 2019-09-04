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
struct kobject {int /*<<< orphan*/  sd; } ;
struct kernfs_node {int dummy; } ;
struct attribute {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kernfs_break_active_protection (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_find_and_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_get (struct kobject*) ; 

struct kernfs_node *sysfs_break_active_protection(struct kobject *kobj,
						  const struct attribute *attr)
{
	struct kernfs_node *kn;

	kobject_get(kobj);
	kn = kernfs_find_and_get(kobj->sd, attr->name);
	if (kn)
		kernfs_break_active_protection(kn);
	return kn;
}