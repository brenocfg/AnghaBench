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
struct TYPE_2__ {void* (* initial_ns ) () ;} ;

/* Variables and functions */
 int KOBJ_NS_TYPES ; 
 int KOBJ_NS_TYPE_NONE ; 
 TYPE_1__** kobj_ns_ops_tbl ; 
 int /*<<< orphan*/  kobj_ns_type_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void* stub1 () ; 

const void *kobj_ns_initial(enum kobj_ns_type type)
{
	const void *ns = NULL;

	spin_lock(&kobj_ns_type_lock);
	if ((type > KOBJ_NS_TYPE_NONE) && (type < KOBJ_NS_TYPES) &&
	    kobj_ns_ops_tbl[type])
		ns = kobj_ns_ops_tbl[type]->initial_ns();
	spin_unlock(&kobj_ns_type_lock);

	return ns;
}