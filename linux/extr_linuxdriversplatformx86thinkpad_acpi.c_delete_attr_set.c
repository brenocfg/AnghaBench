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
struct attribute_set {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_attr_set (struct attribute_set*) ; 
 int /*<<< orphan*/  sysfs_remove_group (struct kobject*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delete_attr_set(struct attribute_set *s, struct kobject *kobj)
{
	sysfs_remove_group(kobj, &s->group);
	destroy_attr_set(s);
}