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
struct cgroup_subsys_state {int id; int /*<<< orphan*/  rstat_css_node; int /*<<< orphan*/  parent; int /*<<< orphan*/  online_cnt; scalar_t__ serial_nr; int /*<<< orphan*/  children; int /*<<< orphan*/  sibling; struct cgroup_subsys* ss; struct cgroup* cgroup; } ;
struct cgroup_subsys {scalar_t__ css_rstat_flush; } ;
struct cgroup {int /*<<< orphan*/  rstat_css_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_css (struct cgroup*,struct cgroup_subsys*) ; 
 int /*<<< orphan*/  cgroup_get_live (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 scalar_t__ cgroup_on_dfl (struct cgroup*) ; 
 struct cgroup* cgroup_parent (struct cgroup*) ; 
 int /*<<< orphan*/  css_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_serial_nr_next ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct cgroup_subsys_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_and_link_css(struct cgroup_subsys_state *css,
			      struct cgroup_subsys *ss, struct cgroup *cgrp)
{
	lockdep_assert_held(&cgroup_mutex);

	cgroup_get_live(cgrp);

	memset(css, 0, sizeof(*css));
	css->cgroup = cgrp;
	css->ss = ss;
	css->id = -1;
	INIT_LIST_HEAD(&css->sibling);
	INIT_LIST_HEAD(&css->children);
	INIT_LIST_HEAD(&css->rstat_css_node);
	css->serial_nr = css_serial_nr_next++;
	atomic_set(&css->online_cnt, 0);

	if (cgroup_parent(cgrp)) {
		css->parent = cgroup_css(cgroup_parent(cgrp), ss);
		css_get(css->parent);
	}

	if (cgroup_on_dfl(cgrp) && ss->css_rstat_flush)
		list_add_rcu(&css->rstat_css_node, &cgrp->rstat_css_list);

	BUG_ON(cgroup_css(cgrp, ss));
}