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
struct cgroup_subsys_state {int dummy; } ;
struct cgroup_file {int /*<<< orphan*/  notify_timer; int /*<<< orphan*/ * kn; } ;
struct cgroup {int /*<<< orphan*/  kn; } ;
struct cftype {int file_offset; int /*<<< orphan*/  ss; } ;

/* Variables and functions */
 int CGROUP_FILE_NAME_MAX ; 
 struct cgroup_subsys_state* cgroup_css (struct cgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_file_kn_lock ; 
 int /*<<< orphan*/  cgroup_file_name (struct cgroup*,struct cftype const*,char*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernfs_remove_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgroup_rm_file(struct cgroup *cgrp, const struct cftype *cft)
{
	char name[CGROUP_FILE_NAME_MAX];

	lockdep_assert_held(&cgroup_mutex);

	if (cft->file_offset) {
		struct cgroup_subsys_state *css = cgroup_css(cgrp, cft->ss);
		struct cgroup_file *cfile = (void *)css + cft->file_offset;

		spin_lock_irq(&cgroup_file_kn_lock);
		cfile->kn = NULL;
		spin_unlock_irq(&cgroup_file_kn_lock);

		del_timer_sync(&cfile->notify_timer);
	}

	kernfs_remove_by_name(cgrp->kn, cgroup_file_name(cgrp, cft, name));
}