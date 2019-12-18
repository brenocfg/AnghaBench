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

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_PTRACE ; 
 int EPERM ; 
#define  YAMA_SCOPE_CAPABILITY 129 
#define  YAMA_SCOPE_NO_ATTACH 128 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  has_ns_capability (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ptrace_scope ; 
 int /*<<< orphan*/  report_access (char*,int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int yama_ptrace_traceme(struct task_struct *parent)
{
	int rc = 0;

	/* Only disallow PTRACE_TRACEME on more aggressive settings. */
	switch (ptrace_scope) {
	case YAMA_SCOPE_CAPABILITY:
		if (!has_ns_capability(parent, current_user_ns(), CAP_SYS_PTRACE))
			rc = -EPERM;
		break;
	case YAMA_SCOPE_NO_ATTACH:
		rc = -EPERM;
		break;
	}

	if (rc) {
		task_lock(current);
		report_access("traceme", current, parent);
		task_unlock(current);
	}

	return rc;
}