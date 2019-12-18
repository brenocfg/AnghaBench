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
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct cgroup_subsys_state {struct cgroup* cgroup; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 struct cgroup* ERR_CAST (struct cgroup_subsys_state*) ; 
 struct cgroup* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  cgroup_on_dfl (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_put (struct cgroup*) ; 
 struct cgroup_subsys_state* css_tryget_online_from_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct file* fget_raw (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 

struct cgroup *cgroup_get_from_fd(int fd)
{
	struct cgroup_subsys_state *css;
	struct cgroup *cgrp;
	struct file *f;

	f = fget_raw(fd);
	if (!f)
		return ERR_PTR(-EBADF);

	css = css_tryget_online_from_dir(f->f_path.dentry, NULL);
	fput(f);
	if (IS_ERR(css))
		return ERR_CAST(css);

	cgrp = css->cgroup;
	if (!cgroup_on_dfl(cgrp)) {
		cgroup_put(cgrp);
		return ERR_PTR(-EBADF);
	}

	return cgrp;
}