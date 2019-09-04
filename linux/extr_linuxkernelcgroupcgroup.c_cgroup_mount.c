#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
struct cgroup_namespace {int /*<<< orphan*/  user_ns; } ;
struct TYPE_7__ {int /*<<< orphan*/  cgrp; } ;
struct TYPE_6__ {TYPE_1__* nsproxy; } ;
struct TYPE_5__ {struct cgroup_namespace* cgroup_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CGROUP2_SUPER_MAGIC ; 
 int /*<<< orphan*/  CGROUP_SUPER_MAGIC ; 
 int EPERM ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  apply_cgroup_root_flags (unsigned int) ; 
 struct dentry* cgroup1_mount (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ,struct cgroup_namespace*) ; 
 struct file_system_type cgroup2_fs_type ; 
 struct dentry* cgroup_do_mount (struct file_system_type*,int,TYPE_3__*,int /*<<< orphan*/ ,struct cgroup_namespace*) ; 
 int /*<<< orphan*/  cgroup_enable_task_cg_lists () ; 
 int /*<<< orphan*/  cgroup_fs_type ; 
 int /*<<< orphan*/  cgroup_get_live (int /*<<< orphan*/ *) ; 
 TYPE_3__ cgrp_dfl_root ; 
 int cgrp_dfl_visible ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  get_cgroup_ns (struct cgroup_namespace*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_cgroup_root_flags (void*,unsigned int*) ; 
 int /*<<< orphan*/  put_cgroup_ns (struct cgroup_namespace*) ; 
 int /*<<< orphan*/  use_task_css_set_links ; 

__attribute__((used)) static struct dentry *cgroup_mount(struct file_system_type *fs_type,
			 int flags, const char *unused_dev_name,
			 void *data)
{
	struct cgroup_namespace *ns = current->nsproxy->cgroup_ns;
	struct dentry *dentry;
	int ret;

	get_cgroup_ns(ns);

	/* Check if the caller has permission to mount. */
	if (!ns_capable(ns->user_ns, CAP_SYS_ADMIN)) {
		put_cgroup_ns(ns);
		return ERR_PTR(-EPERM);
	}

	/*
	 * The first time anyone tries to mount a cgroup, enable the list
	 * linking each css_set to its tasks and fix up all existing tasks.
	 */
	if (!use_task_css_set_links)
		cgroup_enable_task_cg_lists();

	if (fs_type == &cgroup2_fs_type) {
		unsigned int root_flags;

		ret = parse_cgroup_root_flags(data, &root_flags);
		if (ret) {
			put_cgroup_ns(ns);
			return ERR_PTR(ret);
		}

		cgrp_dfl_visible = true;
		cgroup_get_live(&cgrp_dfl_root.cgrp);

		dentry = cgroup_do_mount(&cgroup2_fs_type, flags, &cgrp_dfl_root,
					 CGROUP2_SUPER_MAGIC, ns);
		if (!IS_ERR(dentry))
			apply_cgroup_root_flags(root_flags);
	} else {
		dentry = cgroup1_mount(&cgroup_fs_type, flags, data,
				       CGROUP_SUPER_MAGIC, ns);
	}

	put_cgroup_ns(ns);
	return dentry;
}