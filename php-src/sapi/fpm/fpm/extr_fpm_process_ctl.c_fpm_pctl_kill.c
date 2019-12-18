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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
#define  FPM_PCTL_CONT 131 
#define  FPM_PCTL_QUIT 130 
#define  FPM_PCTL_STOP 129 
#define  FPM_PCTL_TERM 128 
 int SIGCONT ; 
 int SIGQUIT ; 
 int SIGSTOP ; 
 int SIGTERM ; 
 int kill (int /*<<< orphan*/ ,int) ; 

int fpm_pctl_kill(pid_t pid, int how) /* {{{ */
{
	int s = 0;

	switch (how) {
		case FPM_PCTL_TERM :
			s = SIGTERM;
			break;
		case FPM_PCTL_STOP :
			s = SIGSTOP;
			break;
		case FPM_PCTL_CONT :
			s = SIGCONT;
			break;
		case FPM_PCTL_QUIT :
			s = SIGQUIT;
			break;
		default :
			break;
	}
	return kill(pid, s);
}