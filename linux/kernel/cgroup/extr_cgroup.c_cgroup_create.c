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
struct cgroup_root {int /*<<< orphan*/  cgroup_idr; int /*<<< orphan*/  nr_cgrps; } ;
struct TYPE_4__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  children; int /*<<< orphan*/  sibling; scalar_t__ serial_nr; struct TYPE_4__* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_frozen_descendants; scalar_t__ e_freeze; } ;
struct cgroup {int level; scalar_t__ id; scalar_t__* ancestor_ids; TYPE_2__ self; int /*<<< orphan*/  subtree_control; int /*<<< orphan*/  flags; TYPE_1__ freezer; int /*<<< orphan*/  nr_descendants; struct cgroup_root* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_CPUSET_CLONE_CHILDREN ; 
 int /*<<< orphan*/  CGRP_FREEZE ; 
 int /*<<< orphan*/  CGRP_FROZEN ; 
 int /*<<< orphan*/  CGRP_NOTIFY_ON_RELEASE ; 
 int ENOMEM ; 
 struct cgroup* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ancestor_ids ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int cgroup_bpf_inherit (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_control (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_get_live (struct cgroup*) ; 
 scalar_t__ cgroup_idr_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cgroup_idr_replace (int /*<<< orphan*/ *,struct cgroup*,scalar_t__) ; 
 scalar_t__ cgroup_on_dfl (struct cgroup*) ; 
 struct cgroup* cgroup_parent (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_propagate_control (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_rstat_exit (struct cgroup*) ; 
 int cgroup_rstat_init (struct cgroup*) ; 
 int /*<<< orphan*/  css_release ; 
 int /*<<< orphan*/  css_serial_nr_next ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  init_cgroup_housekeeping (struct cgroup*) ; 
 int /*<<< orphan*/  kfree (struct cgroup*) ; 
 struct cgroup* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ notify_on_release (struct cgroup*) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 int percpu_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int psi_cgroup_alloc (struct cgroup*) ; 
 int /*<<< orphan*/  psi_cgroup_free (struct cgroup*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct cgroup*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cgroup *cgroup_create(struct cgroup *parent)
{
	struct cgroup_root *root = parent->root;
	struct cgroup *cgrp, *tcgrp;
	int level = parent->level + 1;
	int ret;

	/* allocate the cgroup and its ID, 0 is reserved for the root */
	cgrp = kzalloc(struct_size(cgrp, ancestor_ids, (level + 1)),
		       GFP_KERNEL);
	if (!cgrp)
		return ERR_PTR(-ENOMEM);

	ret = percpu_ref_init(&cgrp->self.refcnt, css_release, 0, GFP_KERNEL);
	if (ret)
		goto out_free_cgrp;

	if (cgroup_on_dfl(parent)) {
		ret = cgroup_rstat_init(cgrp);
		if (ret)
			goto out_cancel_ref;
	}

	/*
	 * Temporarily set the pointer to NULL, so idr_find() won't return
	 * a half-baked cgroup.
	 */
	cgrp->id = cgroup_idr_alloc(&root->cgroup_idr, NULL, 2, 0, GFP_KERNEL);
	if (cgrp->id < 0) {
		ret = -ENOMEM;
		goto out_stat_exit;
	}

	init_cgroup_housekeeping(cgrp);

	cgrp->self.parent = &parent->self;
	cgrp->root = root;
	cgrp->level = level;

	ret = psi_cgroup_alloc(cgrp);
	if (ret)
		goto out_idr_free;

	ret = cgroup_bpf_inherit(cgrp);
	if (ret)
		goto out_psi_free;

	/*
	 * New cgroup inherits effective freeze counter, and
	 * if the parent has to be frozen, the child has too.
	 */
	cgrp->freezer.e_freeze = parent->freezer.e_freeze;
	if (cgrp->freezer.e_freeze) {
		/*
		 * Set the CGRP_FREEZE flag, so when a process will be
		 * attached to the child cgroup, it will become frozen.
		 * At this point the new cgroup is unpopulated, so we can
		 * consider it frozen immediately.
		 */
		set_bit(CGRP_FREEZE, &cgrp->flags);
		set_bit(CGRP_FROZEN, &cgrp->flags);
	}

	spin_lock_irq(&css_set_lock);
	for (tcgrp = cgrp; tcgrp; tcgrp = cgroup_parent(tcgrp)) {
		cgrp->ancestor_ids[tcgrp->level] = tcgrp->id;

		if (tcgrp != cgrp) {
			tcgrp->nr_descendants++;

			/*
			 * If the new cgroup is frozen, all ancestor cgroups
			 * get a new frozen descendant, but their state can't
			 * change because of this.
			 */
			if (cgrp->freezer.e_freeze)
				tcgrp->freezer.nr_frozen_descendants++;
		}
	}
	spin_unlock_irq(&css_set_lock);

	if (notify_on_release(parent))
		set_bit(CGRP_NOTIFY_ON_RELEASE, &cgrp->flags);

	if (test_bit(CGRP_CPUSET_CLONE_CHILDREN, &parent->flags))
		set_bit(CGRP_CPUSET_CLONE_CHILDREN, &cgrp->flags);

	cgrp->self.serial_nr = css_serial_nr_next++;

	/* allocation complete, commit to creation */
	list_add_tail_rcu(&cgrp->self.sibling, &cgroup_parent(cgrp)->self.children);
	atomic_inc(&root->nr_cgrps);
	cgroup_get_live(parent);

	/*
	 * @cgrp is now fully operational.  If something fails after this
	 * point, it'll be released via the normal destruction path.
	 */
	cgroup_idr_replace(&root->cgroup_idr, cgrp, cgrp->id);

	/*
	 * On the default hierarchy, a child doesn't automatically inherit
	 * subtree_control from the parent.  Each is configured manually.
	 */
	if (!cgroup_on_dfl(cgrp))
		cgrp->subtree_control = cgroup_control(cgrp);

	cgroup_propagate_control(cgrp);

	return cgrp;

out_psi_free:
	psi_cgroup_free(cgrp);
out_idr_free:
	cgroup_idr_remove(&root->cgroup_idr, cgrp->id);
out_stat_exit:
	if (cgroup_on_dfl(parent))
		cgroup_rstat_exit(cgrp);
out_cancel_ref:
	percpu_ref_exit(&cgrp->self.refcnt);
out_free_cgrp:
	kfree(cgrp);
	return ERR_PTR(ret);
}