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
struct vfree_deferred {int /*<<< orphan*/  wq; int /*<<< orphan*/  list; } ;
struct llist_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ llist_add (struct llist_node*,int /*<<< orphan*/ *) ; 
 struct vfree_deferred* raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree_deferred ; 

__attribute__((used)) static inline void __vfree_deferred(const void *addr)
{
	/*
	 * Use raw_cpu_ptr() because this can be called from preemptible
	 * context. Preemption is absolutely fine here, because the llist_add()
	 * implementation is lockless, so it works even if we are adding to
	 * nother cpu's list.  schedule_work() should be fine with this too.
	 */
	struct vfree_deferred *p = raw_cpu_ptr(&vfree_deferred);

	if (llist_add((struct llist_node *)addr, &p->list))
		schedule_work(&p->wq);
}