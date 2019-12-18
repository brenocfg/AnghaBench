#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pid_namespace {struct pid_namespace* parent; } ;
struct ns_common {int dummy; } ;
struct TYPE_4__ {struct ns_common ns; } ;
struct TYPE_3__ {struct pid_namespace* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 struct ns_common* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 TYPE_2__* get_pid_ns (struct pid_namespace*) ; 
 struct pid_namespace* task_active_pid_ns (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_pid_ns (struct ns_common*) ; 

__attribute__((used)) static struct ns_common *pidns_get_parent(struct ns_common *ns)
{
	struct pid_namespace *active = task_active_pid_ns(current);
	struct pid_namespace *pid_ns, *p;

	/* See if the parent is in the current namespace */
	pid_ns = p = to_pid_ns(ns)->parent;
	for (;;) {
		if (!p)
			return ERR_PTR(-EPERM);
		if (p == active)
			break;
		p = p->parent;
	}

	return &get_pid_ns(pid_ns)->ns;
}