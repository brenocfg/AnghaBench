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
struct task_struct {int dummy; } ;
struct cgroup_cls_state {int dummy; } ;

/* Variables and functions */
 struct cgroup_cls_state* css_cls_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_cls_cgrp_id ; 
 int /*<<< orphan*/  rcu_read_lock_bh_held () ; 
 int /*<<< orphan*/  task_css_check (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct cgroup_cls_state *task_cls_state(struct task_struct *p)
{
	return css_cls_state(task_css_check(p, net_cls_cgrp_id,
					    rcu_read_lock_bh_held()));
}