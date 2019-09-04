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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  profiles; } ;
struct aa_ns {int /*<<< orphan*/  lock; TYPE_1__ labels; struct aa_ns* parent; int /*<<< orphan*/  sub_ns; TYPE_2__ base; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aa_profile_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __aa_proxy_redirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __aafs_ns_rmdir (struct aa_ns*) ; 
 int /*<<< orphan*/  __ns_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_unconfined (struct aa_ns*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void destroy_ns(struct aa_ns *ns)
{
	if (!ns)
		return;

	mutex_lock_nested(&ns->lock, ns->level);
	/* release all profiles in this namespace */
	__aa_profile_list_release(&ns->base.profiles);

	/* release all sub namespaces */
	__ns_list_release(&ns->sub_ns);

	if (ns->parent) {
		unsigned long flags;

		write_lock_irqsave(&ns->labels.lock, flags);
		__aa_proxy_redirect(ns_unconfined(ns),
				    ns_unconfined(ns->parent));
		write_unlock_irqrestore(&ns->labels.lock, flags);
	}
	__aafs_ns_rmdir(ns);
	mutex_unlock(&ns->lock);
}