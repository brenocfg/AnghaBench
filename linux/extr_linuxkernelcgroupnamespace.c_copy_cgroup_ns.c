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
struct user_namespace {int dummy; } ;
struct ucounts {int dummy; } ;
struct css_set {int dummy; } ;
struct cgroup_namespace {struct css_set* root_cset; struct ucounts* ucounts; int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 unsigned long CLONE_NEWCGROUP ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  EPERM ; 
 struct cgroup_namespace* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct cgroup_namespace*) ; 
 struct cgroup_namespace* alloc_cgroup_ns () ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dec_cgroup_namespaces (struct ucounts*) ; 
 int /*<<< orphan*/  get_cgroup_ns (struct cgroup_namespace*) ; 
 int /*<<< orphan*/  get_css_set (struct css_set*) ; 
 int /*<<< orphan*/  get_user_ns (struct user_namespace*) ; 
 struct ucounts* inc_cgroup_namespaces (struct user_namespace*) ; 
 int /*<<< orphan*/  ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_css_set (struct css_set*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct css_set* task_css_set (int /*<<< orphan*/ ) ; 

struct cgroup_namespace *copy_cgroup_ns(unsigned long flags,
					struct user_namespace *user_ns,
					struct cgroup_namespace *old_ns)
{
	struct cgroup_namespace *new_ns;
	struct ucounts *ucounts;
	struct css_set *cset;

	BUG_ON(!old_ns);

	if (!(flags & CLONE_NEWCGROUP)) {
		get_cgroup_ns(old_ns);
		return old_ns;
	}

	/* Allow only sysadmin to create cgroup namespace. */
	if (!ns_capable(user_ns, CAP_SYS_ADMIN))
		return ERR_PTR(-EPERM);

	ucounts = inc_cgroup_namespaces(user_ns);
	if (!ucounts)
		return ERR_PTR(-ENOSPC);

	/* It is not safe to take cgroup_mutex here */
	spin_lock_irq(&css_set_lock);
	cset = task_css_set(current);
	get_css_set(cset);
	spin_unlock_irq(&css_set_lock);

	new_ns = alloc_cgroup_ns();
	if (IS_ERR(new_ns)) {
		put_css_set(cset);
		dec_cgroup_namespaces(ucounts);
		return new_ns;
	}

	new_ns->user_ns = get_user_ns(user_ns);
	new_ns->ucounts = ucounts;
	new_ns->root_cset = cset;

	return new_ns;
}