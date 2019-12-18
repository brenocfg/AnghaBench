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
struct pid_namespace {scalar_t__ bacct; struct pid_namespace* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  slow_acct_process (struct pid_namespace*) ; 
 struct pid_namespace* task_active_pid_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (struct pid_namespace*) ; 

void acct_process(void)
{
	struct pid_namespace *ns;

	/*
	 * This loop is safe lockless, since current is still
	 * alive and holds its namespace, which in turn holds
	 * its parent.
	 */
	for (ns = task_active_pid_ns(current); ns != NULL; ns = ns->parent) {
		if (ns->bacct)
			break;
	}
	if (unlikely(ns))
		slow_acct_process(ns);
}