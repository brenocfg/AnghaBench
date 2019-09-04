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
struct pids_cgroup {scalar_t__ limit; } ;
struct kernfs_open_file {int dummy; } ;
struct cgroup_subsys_state {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PIDS_MAX ; 
 int /*<<< orphan*/  PIDS_MAX_STR ; 
 struct pids_cgroup* css_pids (struct cgroup_subsys_state*) ; 
 int kstrtoll (char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct cgroup_subsys_state* of_css (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strstrip (char*) ; 

__attribute__((used)) static ssize_t pids_max_write(struct kernfs_open_file *of, char *buf,
			      size_t nbytes, loff_t off)
{
	struct cgroup_subsys_state *css = of_css(of);
	struct pids_cgroup *pids = css_pids(css);
	int64_t limit;
	int err;

	buf = strstrip(buf);
	if (!strcmp(buf, PIDS_MAX_STR)) {
		limit = PIDS_MAX;
		goto set_limit;
	}

	err = kstrtoll(buf, 0, &limit);
	if (err)
		return err;

	if (limit < 0 || limit >= PIDS_MAX)
		return -EINVAL;

set_limit:
	/*
	 * Limit updates don't need to be mutex'd, since it isn't
	 * critical that any racing fork()s follow the new limit.
	 */
	pids->limit = limit;
	return nbytes;
}