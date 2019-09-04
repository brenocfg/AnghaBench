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
struct pids_cgroup {struct cgroup_subsys_state css; int /*<<< orphan*/  events_limit; int /*<<< orphan*/  counter; int /*<<< orphan*/  limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct cgroup_subsys_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIDS_MAX ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pids_cgroup* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cgroup_subsys_state *
pids_css_alloc(struct cgroup_subsys_state *parent)
{
	struct pids_cgroup *pids;

	pids = kzalloc(sizeof(struct pids_cgroup), GFP_KERNEL);
	if (!pids)
		return ERR_PTR(-ENOMEM);

	pids->limit = PIDS_MAX;
	atomic64_set(&pids->counter, 0);
	atomic64_set(&pids->events_limit, 0);
	return &pids->css;
}