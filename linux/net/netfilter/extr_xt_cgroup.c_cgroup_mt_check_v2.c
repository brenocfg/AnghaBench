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
struct xt_mtchk_param {struct xt_cgroup_info_v2* matchinfo; } ;
struct xt_cgroup_info_v2 {int invert_path; int invert_classid; struct cgroup* priv; int /*<<< orphan*/  path; scalar_t__ has_path; scalar_t__ has_classid; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct cgroup*) ; 
 int /*<<< orphan*/  PTR_ERR (struct cgroup*) ; 
 struct cgroup* cgroup_get_from_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,...) ; 

__attribute__((used)) static int cgroup_mt_check_v2(const struct xt_mtchk_param *par)
{
	struct xt_cgroup_info_v2 *info = par->matchinfo;
	struct cgroup *cgrp;

	if ((info->invert_path & ~1) || (info->invert_classid & ~1))
		return -EINVAL;

	if (!info->has_path && !info->has_classid) {
		pr_info("xt_cgroup: no path or classid specified\n");
		return -EINVAL;
	}

	if (info->has_path && info->has_classid) {
		pr_info_ratelimited("path and classid specified\n");
		return -EINVAL;
	}

	info->priv = NULL;
	if (info->has_path) {
		cgrp = cgroup_get_from_path(info->path);
		if (IS_ERR(cgrp)) {
			pr_info_ratelimited("invalid path, errno=%ld\n",
					    PTR_ERR(cgrp));
			return -EINVAL;
		}
		info->priv = cgrp;
	}

	return 0;
}