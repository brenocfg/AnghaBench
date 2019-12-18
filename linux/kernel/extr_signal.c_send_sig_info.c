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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int do_send_sig_info (int,struct kernel_siginfo*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_signal (int) ; 

int send_sig_info(int sig, struct kernel_siginfo *info, struct task_struct *p)
{
	/*
	 * Make sure legacy kernel users don't send in bad values
	 * (normal paths check this in check_kill_permission).
	 */
	if (!valid_signal(sig))
		return -EINVAL;

	return do_send_sig_info(sig, info, p, PIDTYPE_PID);
}