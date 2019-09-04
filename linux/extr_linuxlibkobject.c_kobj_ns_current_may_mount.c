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
typedef  enum kobj_ns_type { ____Placeholder_kobj_ns_type } kobj_ns_type ;
struct TYPE_2__ {int (* current_may_mount ) () ;} ;

/* Variables and functions */
 int KOBJ_NS_TYPES ; 
 int KOBJ_NS_TYPE_NONE ; 
 TYPE_1__** kobj_ns_ops_tbl ; 
 int /*<<< orphan*/  kobj_ns_type_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 () ; 

bool kobj_ns_current_may_mount(enum kobj_ns_type type)
{
	bool may_mount = true;

	spin_lock(&kobj_ns_type_lock);
	if ((type > KOBJ_NS_TYPE_NONE) && (type < KOBJ_NS_TYPES) &&
	    kobj_ns_ops_tbl[type])
		may_mount = kobj_ns_ops_tbl[type]->current_may_mount();
	spin_unlock(&kobj_ns_type_lock);

	return may_mount;
}