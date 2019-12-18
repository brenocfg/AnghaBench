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
struct kobject {int /*<<< orphan*/  parent; } ;
struct kobj_ns_type_operations {int dummy; } ;

/* Variables and functions */
 struct kobj_ns_type_operations const* kobj_child_ns_ops (int /*<<< orphan*/ ) ; 

const struct kobj_ns_type_operations *kobj_ns_ops(struct kobject *kobj)
{
	return kobj_child_ns_ops(kobj->parent);
}