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
struct kobj_ns_type_operations {scalar_t__ type; } ;
struct TYPE_2__ {void const* (* namespace ) (struct kobject*) ;} ;

/* Variables and functions */
 scalar_t__ KOBJ_NS_TYPE_NONE ; 
 struct kobj_ns_type_operations* kobj_ns_ops (struct kobject*) ; 
 void const* stub1 (struct kobject*) ; 

const void *kobject_namespace(struct kobject *kobj)
{
	const struct kobj_ns_type_operations *ns_ops = kobj_ns_ops(kobj);

	if (!ns_ops || ns_ops->type == KOBJ_NS_TYPE_NONE)
		return NULL;

	return kobj->ktype->namespace(kobj);
}