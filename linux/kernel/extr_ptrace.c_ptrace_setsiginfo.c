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
struct task_struct {int /*<<< orphan*/ * last_siginfo; } ;
typedef  int /*<<< orphan*/  kernel_siginfo_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  copy_siginfo (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ lock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static int ptrace_setsiginfo(struct task_struct *child, const kernel_siginfo_t *info)
{
	unsigned long flags;
	int error = -ESRCH;

	if (lock_task_sighand(child, &flags)) {
		error = -EINVAL;
		if (likely(child->last_siginfo != NULL)) {
			copy_siginfo(child->last_siginfo, info);
			error = 0;
		}
		unlock_task_sighand(child, &flags);
	}
	return error;
}