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
struct lock_class_key {int dummy; } ;
struct kernfs_node {int dummy; } ;
struct cgroup_subsys_state {int dummy; } ;
struct cgroup_file {struct kernfs_node* kn; int /*<<< orphan*/  notify_timer; } ;
struct cgroup {int /*<<< orphan*/  kn; } ;
struct cftype {int file_offset; int /*<<< orphan*/  kf_ops; struct lock_class_key lockdep_key; } ;

/* Variables and functions */
 int CGROUP_FILE_NAME_MAX ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ IS_ERR (struct kernfs_node*) ; 
 int PTR_ERR (struct kernfs_node*) ; 
 struct kernfs_node* __kernfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cftype*,int /*<<< orphan*/ *,struct lock_class_key*) ; 
 int /*<<< orphan*/  cgroup_file_kn_lock ; 
 int /*<<< orphan*/  cgroup_file_mode (struct cftype*) ; 
 int /*<<< orphan*/  cgroup_file_name (struct cgroup*,struct cftype*,char*) ; 
 int /*<<< orphan*/  cgroup_file_notify_timer ; 
 int cgroup_kn_set_ugid (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_remove (struct kernfs_node*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cgroup_add_file(struct cgroup_subsys_state *css, struct cgroup *cgrp,
			   struct cftype *cft)
{
	char name[CGROUP_FILE_NAME_MAX];
	struct kernfs_node *kn;
	struct lock_class_key *key = NULL;
	int ret;

#ifdef CONFIG_DEBUG_LOCK_ALLOC
	key = &cft->lockdep_key;
#endif
	kn = __kernfs_create_file(cgrp->kn, cgroup_file_name(cgrp, cft, name),
				  cgroup_file_mode(cft),
				  GLOBAL_ROOT_UID, GLOBAL_ROOT_GID,
				  0, cft->kf_ops, cft,
				  NULL, key);
	if (IS_ERR(kn))
		return PTR_ERR(kn);

	ret = cgroup_kn_set_ugid(kn);
	if (ret) {
		kernfs_remove(kn);
		return ret;
	}

	if (cft->file_offset) {
		struct cgroup_file *cfile = (void *)css + cft->file_offset;

		timer_setup(&cfile->notify_timer, cgroup_file_notify_timer, 0);

		spin_lock_irq(&cgroup_file_kn_lock);
		cfile->kn = kn;
		spin_unlock_irq(&cgroup_file_kn_lock);
	}

	return 0;
}