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
struct ctl_table_header {struct completion* unregistering; int /*<<< orphan*/  used; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct completion* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erase_header (struct ctl_table_header*) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  proc_sys_prune_dcache (struct ctl_table_header*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_lock ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

__attribute__((used)) static void start_unregistering(struct ctl_table_header *p)
{
	/*
	 * if p->used is 0, nobody will ever touch that entry again;
	 * we'll eliminate all paths to it before dropping sysctl_lock
	 */
	if (unlikely(p->used)) {
		struct completion wait;
		init_completion(&wait);
		p->unregistering = &wait;
		spin_unlock(&sysctl_lock);
		wait_for_completion(&wait);
	} else {
		/* anything non-NULL; we'll never dereference it */
		p->unregistering = ERR_PTR(-EINVAL);
		spin_unlock(&sysctl_lock);
	}
	/*
	 * Prune dentries for unregistered sysctls: namespaced sysctls
	 * can have duplicate names and contaminate dcache very badly.
	 */
	proc_sys_prune_dcache(p);
	/*
	 * do not remove from the list until nobody holds it; walking the
	 * list in do_sysctl() relies on that.
	 */
	spin_lock(&sysctl_lock);
	erase_header(p);
}