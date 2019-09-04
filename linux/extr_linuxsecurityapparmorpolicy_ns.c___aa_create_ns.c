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
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/  name; int /*<<< orphan*/  hname; } ;
struct aa_ns {int /*<<< orphan*/  lock; int /*<<< orphan*/  sub_ns; TYPE_1__ base; int /*<<< orphan*/  parent; scalar_t__ level; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_ERROR (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct aa_ns* ERR_PTR (int) ; 
 int __aafs_ns_mkdir (struct aa_ns*,int /*<<< orphan*/ ,char const*,struct dentry*) ; 
 int /*<<< orphan*/  aa_free_ns (struct aa_ns*) ; 
 int /*<<< orphan*/  aa_get_ns (struct aa_ns*) ; 
 struct aa_ns* alloc_ns (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_subns_dir (struct aa_ns*) ; 

__attribute__((used)) static struct aa_ns *__aa_create_ns(struct aa_ns *parent, const char *name,
				    struct dentry *dir)
{
	struct aa_ns *ns;
	int error;

	AA_BUG(!parent);
	AA_BUG(!name);
	AA_BUG(!mutex_is_locked(&parent->lock));

	ns = alloc_ns(parent->base.hname, name);
	if (!ns)
		return ERR_PTR(-ENOMEM);
	ns->level = parent->level + 1;
	mutex_lock_nested(&ns->lock, ns->level);
	error = __aafs_ns_mkdir(ns, ns_subns_dir(parent), name, dir);
	if (error) {
		AA_ERROR("Failed to create interface for ns %s\n",
			 ns->base.name);
		mutex_unlock(&ns->lock);
		aa_free_ns(ns);
		return ERR_PTR(error);
	}
	ns->parent = aa_get_ns(parent);
	list_add_rcu(&ns->base.list, &parent->sub_ns);
	/* add list ref */
	aa_get_ns(ns);
	mutex_unlock(&ns->lock);

	return ns;
}