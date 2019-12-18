#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kernfs_open_file {TYPE_2__* kn; } ;
struct cgroup_subsys_state {int dummy; } ;
struct cgroup {struct cgroup_subsys_state self; int /*<<< orphan*/ * subsys; } ;
struct cftype {TYPE_3__* ss; } ;
struct TYPE_6__ {size_t id; } ;
struct TYPE_5__ {TYPE_1__* parent; } ;
struct TYPE_4__ {struct cgroup* priv; } ;

/* Variables and functions */
 struct cftype* of_cft (struct kernfs_open_file*) ; 
 struct cgroup_subsys_state* rcu_dereference_raw (int /*<<< orphan*/ ) ; 

struct cgroup_subsys_state *of_css(struct kernfs_open_file *of)
{
	struct cgroup *cgrp = of->kn->parent->priv;
	struct cftype *cft = of_cft(of);

	/*
	 * This is open and unprotected implementation of cgroup_css().
	 * seq_css() is only called from a kernfs file operation which has
	 * an active reference on the file.  Because all the subsystem
	 * files are drained before a css is disassociated with a cgroup,
	 * the matching css from the cgroup's subsys table is guaranteed to
	 * be and stay valid until the enclosing operation is complete.
	 */
	if (cft->ss)
		return rcu_dereference_raw(cgrp->subsys[cft->ss->id]);
	else
		return &cgrp->self;
}