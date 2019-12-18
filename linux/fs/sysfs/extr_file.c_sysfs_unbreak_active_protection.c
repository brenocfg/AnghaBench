#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct kernfs_node {TYPE_1__* parent; } ;
struct TYPE_2__ {struct kobject* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_unbreak_active_protection (struct kernfs_node*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 

void sysfs_unbreak_active_protection(struct kernfs_node *kn)
{
	struct kobject *kobj = kn->parent->priv;

	kernfs_unbreak_active_protection(kn);
	kernfs_put(kn);
	kobject_put(kobj);
}