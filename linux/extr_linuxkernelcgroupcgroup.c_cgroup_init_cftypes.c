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
struct kernfs_ops {scalar_t__ atomic_write_len; } ;
struct cgroup_subsys {int dummy; } ;
struct cftype {char* name; scalar_t__ max_write_len; struct cgroup_subsys* ss; struct kernfs_ops* kf_ops; scalar_t__ seq_start; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cgroup_exit_cftypes (struct cftype*) ; 
 struct kernfs_ops cgroup_kf_ops ; 
 struct kernfs_ops cgroup_kf_single_ops ; 
 struct kernfs_ops* kmemdup (struct kernfs_ops*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cgroup_init_cftypes(struct cgroup_subsys *ss, struct cftype *cfts)
{
	struct cftype *cft;

	for (cft = cfts; cft->name[0] != '\0'; cft++) {
		struct kernfs_ops *kf_ops;

		WARN_ON(cft->ss || cft->kf_ops);

		if (cft->seq_start)
			kf_ops = &cgroup_kf_ops;
		else
			kf_ops = &cgroup_kf_single_ops;

		/*
		 * Ugh... if @cft wants a custom max_write_len, we need to
		 * make a copy of kf_ops to set its atomic_write_len.
		 */
		if (cft->max_write_len && cft->max_write_len != PAGE_SIZE) {
			kf_ops = kmemdup(kf_ops, sizeof(*kf_ops), GFP_KERNEL);
			if (!kf_ops) {
				cgroup_exit_cftypes(cfts);
				return -ENOMEM;
			}
			kf_ops->atomic_write_len = cft->max_write_len;
		}

		cft->kf_ops = kf_ops;
		cft->ss = ss;
	}

	return 0;
}