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
struct kernel_siginfo {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*,struct kernel_siginfo*,int,struct cred const*) ; 
 int /*<<< orphan*/  task_kill ; 

int security_task_kill(struct task_struct *p, struct kernel_siginfo *info,
			int sig, const struct cred *cred)
{
	return call_int_hook(task_kill, 0, p, info, sig, cred);
}