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
struct siginfo {int si_signo; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_code; scalar_t__ si_errno; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SI_TKILL ; 
 int /*<<< orphan*/  clear_siginfo (struct siginfo*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int do_send_specific (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct siginfo*) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_tgid_vnr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_tkill(pid_t tgid, pid_t pid, int sig)
{
	struct siginfo info;

	clear_siginfo(&info);
	info.si_signo = sig;
	info.si_errno = 0;
	info.si_code = SI_TKILL;
	info.si_pid = task_tgid_vnr(current);
	info.si_uid = from_kuid_munged(current_user_ns(), current_uid());

	return do_send_specific(tgid, pid, sig, &info);
}