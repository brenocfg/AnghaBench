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
typedef  int u32 ;

/* Variables and functions */
 int SECCOMP_LOG_ERRNO ; 
 int SECCOMP_LOG_KILL_PROCESS ; 
 int SECCOMP_LOG_KILL_THREAD ; 
 int SECCOMP_LOG_LOG ; 
 int SECCOMP_LOG_TRACE ; 
 int SECCOMP_LOG_TRAP ; 
 int SECCOMP_LOG_USER_NOTIF ; 
#define  SECCOMP_RET_ALLOW 135 
#define  SECCOMP_RET_ERRNO 134 
#define  SECCOMP_RET_KILL_PROCESS 133 
#define  SECCOMP_RET_KILL_THREAD 132 
#define  SECCOMP_RET_LOG 131 
#define  SECCOMP_RET_TRACE 130 
#define  SECCOMP_RET_TRAP 129 
#define  SECCOMP_RET_USER_NOTIF 128 
 int /*<<< orphan*/  audit_seccomp (unsigned long,long,int) ; 
 int seccomp_actions_logged ; 

__attribute__((used)) static inline void seccomp_log(unsigned long syscall, long signr, u32 action,
			       bool requested)
{
	bool log = false;

	switch (action) {
	case SECCOMP_RET_ALLOW:
		break;
	case SECCOMP_RET_TRAP:
		log = requested && seccomp_actions_logged & SECCOMP_LOG_TRAP;
		break;
	case SECCOMP_RET_ERRNO:
		log = requested && seccomp_actions_logged & SECCOMP_LOG_ERRNO;
		break;
	case SECCOMP_RET_TRACE:
		log = requested && seccomp_actions_logged & SECCOMP_LOG_TRACE;
		break;
	case SECCOMP_RET_USER_NOTIF:
		log = requested && seccomp_actions_logged & SECCOMP_LOG_USER_NOTIF;
		break;
	case SECCOMP_RET_LOG:
		log = seccomp_actions_logged & SECCOMP_LOG_LOG;
		break;
	case SECCOMP_RET_KILL_THREAD:
		log = seccomp_actions_logged & SECCOMP_LOG_KILL_THREAD;
		break;
	case SECCOMP_RET_KILL_PROCESS:
	default:
		log = seccomp_actions_logged & SECCOMP_LOG_KILL_PROCESS;
	}

	/*
	 * Emit an audit message when the action is RET_KILL_*, RET_LOG, or the
	 * FILTER_FLAG_LOG bit was set. The admin has the ability to silence
	 * any action from being logged by removing the action name from the
	 * seccomp_actions_logged sysctl.
	 */
	if (!log)
		return;

	audit_seccomp(syscall, signr, action);
}