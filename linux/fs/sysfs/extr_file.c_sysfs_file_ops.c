#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sysfs_ops {int dummy; } ;
struct kobject {TYPE_2__* ktype; } ;
struct kernfs_node {int flags; TYPE_1__* parent; } ;
struct TYPE_4__ {struct sysfs_ops const* sysfs_ops; } ;
struct TYPE_3__ {struct kobject* priv; } ;

/* Variables and functions */
 int KERNFS_LOCKDEP ; 
 int /*<<< orphan*/  lockdep_assert_held (struct kernfs_node*) ; 

__attribute__((used)) static const struct sysfs_ops *sysfs_file_ops(struct kernfs_node *kn)
{
	struct kobject *kobj = kn->parent->priv;

	if (kn->flags & KERNFS_LOCKDEP)
		lockdep_assert_held(kn);
	return kobj->ktype ? kobj->ktype->sysfs_ops : NULL;
}