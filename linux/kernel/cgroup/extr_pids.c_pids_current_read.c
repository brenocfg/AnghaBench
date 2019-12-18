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
struct pids_cgroup {int /*<<< orphan*/  counter; } ;
struct cgroup_subsys_state {int dummy; } ;
struct cftype {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 struct pids_cgroup* css_pids (struct cgroup_subsys_state*) ; 

__attribute__((used)) static s64 pids_current_read(struct cgroup_subsys_state *css,
			     struct cftype *cft)
{
	struct pids_cgroup *pids = css_pids(css);

	return atomic64_read(&pids->counter);
}