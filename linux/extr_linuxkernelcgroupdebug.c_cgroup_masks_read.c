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
struct seq_file {struct kernfs_open_file* private; } ;
struct kernfs_open_file {int /*<<< orphan*/  kn; } ;
struct cgroup {int /*<<< orphan*/  subtree_ss_mask; int /*<<< orphan*/  subtree_control; } ;

/* Variables and functions */
 int ENODEV ; 
 struct cgroup* cgroup_kn_lock_live (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cgroup_kn_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_masks_read_one (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cgroup_masks_read(struct seq_file *seq, void *v)
{
	struct kernfs_open_file *of = seq->private;
	struct cgroup *cgrp;

	cgrp = cgroup_kn_lock_live(of->kn, false);
	if (!cgrp)
		return -ENODEV;

	cgroup_masks_read_one(seq, "subtree_control", cgrp->subtree_control);
	cgroup_masks_read_one(seq, "subtree_ss_mask", cgrp->subtree_ss_mask);

	cgroup_kn_unlock(of->kn);
	return 0;
}