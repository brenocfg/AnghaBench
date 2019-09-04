#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {unsigned int ptrace; } ;
struct TYPE_2__ {int ptrace; int /*<<< orphan*/  seccomp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CONFIG_CHECKPOINT_RESTORE ; 
 int /*<<< orphan*/  CONFIG_SECCOMP ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int PTRACE_O_MASK ; 
 unsigned long PTRACE_O_SUSPEND_SECCOMP ; 
 unsigned int PT_OPT_FLAG_SHIFT ; 
 int PT_SUSPEND_SECCOMP ; 
 scalar_t__ SECCOMP_MODE_DISABLED ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 scalar_t__ seccomp_mode (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static int ptrace_setoptions(struct task_struct *child, unsigned long data)
{
	unsigned flags;

	if (data & ~(unsigned long)PTRACE_O_MASK)
		return -EINVAL;

	if (unlikely(data & PTRACE_O_SUSPEND_SECCOMP)) {
		if (!IS_ENABLED(CONFIG_CHECKPOINT_RESTORE) ||
		    !IS_ENABLED(CONFIG_SECCOMP))
			return -EINVAL;

		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;

		if (seccomp_mode(&current->seccomp) != SECCOMP_MODE_DISABLED ||
		    current->ptrace & PT_SUSPEND_SECCOMP)
			return -EPERM;
	}

	/* Avoid intermediate state when all opts are cleared */
	flags = child->ptrace;
	flags &= ~(PTRACE_O_MASK << PT_OPT_FLAG_SHIFT);
	flags |= (data << PT_OPT_FLAG_SHIFT);
	child->ptrace = flags;

	return 0;
}