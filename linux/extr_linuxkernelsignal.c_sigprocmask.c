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
struct task_struct {int /*<<< orphan*/  blocked; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int EINVAL ; 
#define  SIG_BLOCK 130 
#define  SIG_SETMASK 129 
#define  SIG_UNBLOCK 128 
 int /*<<< orphan*/  __set_current_blocked (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  sigandnsets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigorsets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int sigprocmask(int how, sigset_t *set, sigset_t *oldset)
{
	struct task_struct *tsk = current;
	sigset_t newset;

	/* Lockless, only current can change ->blocked, never from irq */
	if (oldset)
		*oldset = tsk->blocked;

	switch (how) {
	case SIG_BLOCK:
		sigorsets(&newset, &tsk->blocked, set);
		break;
	case SIG_UNBLOCK:
		sigandnsets(&newset, &tsk->blocked, set);
		break;
	case SIG_SETMASK:
		newset = *set;
		break;
	default:
		return -EINVAL;
	}

	__set_current_blocked(&newset);
	return 0;
}