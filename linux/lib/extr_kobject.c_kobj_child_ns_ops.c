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
struct kobject {TYPE_1__* ktype; } ;
struct kobj_ns_type_operations {int dummy; } ;
struct TYPE_2__ {struct kobj_ns_type_operations* (* child_ns_type ) (struct kobject*) ;} ;

/* Variables and functions */
 struct kobj_ns_type_operations* stub1 (struct kobject*) ; 

const struct kobj_ns_type_operations *kobj_child_ns_ops(struct kobject *parent)
{
	const struct kobj_ns_type_operations *ops = NULL;

	if (parent && parent->ktype && parent->ktype->child_ns_type)
		ops = parent->ktype->child_ns_type(parent);

	return ops;
}