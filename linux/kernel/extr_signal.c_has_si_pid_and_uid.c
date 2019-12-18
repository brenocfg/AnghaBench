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
struct kernel_siginfo {int /*<<< orphan*/  si_code; int /*<<< orphan*/  si_signo; } ;

/* Variables and functions */
#define  SIL_CHLD 137 
#define  SIL_FAULT 136 
#define  SIL_FAULT_BNDERR 135 
#define  SIL_FAULT_MCEERR 134 
#define  SIL_FAULT_PKUERR 133 
#define  SIL_KILL 132 
#define  SIL_POLL 131 
#define  SIL_RT 130 
#define  SIL_SYS 129 
#define  SIL_TIMER 128 
 int siginfo_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool has_si_pid_and_uid(struct kernel_siginfo *info)
{
	bool ret = false;
	switch (siginfo_layout(info->si_signo, info->si_code)) {
	case SIL_KILL:
	case SIL_CHLD:
	case SIL_RT:
		ret = true;
		break;
	case SIL_TIMER:
	case SIL_POLL:
	case SIL_FAULT:
	case SIL_FAULT_MCEERR:
	case SIL_FAULT_BNDERR:
	case SIL_FAULT_PKUERR:
	case SIL_SYS:
		ret = false;
		break;
	}
	return ret;
}