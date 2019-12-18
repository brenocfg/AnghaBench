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
typedef  int uchar ;
typedef  int pid_t ;

/* Variables and functions */
 int F_NOWAIT ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int fork () ; 
 void* oldsighup ; 
 void* oldsigtstp ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  setsid () ; 
 void* signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pid_t xfork(uchar flag)
{
	pid_t p = fork();

	if (p > 0) {
		/* the parent ignores the interrupt, quit and hangup signals */
		oldsighup = signal(SIGHUP, SIG_IGN);
		oldsigtstp = signal(SIGTSTP, SIG_DFL);
	} else if (p == 0) {
		/* so they can be used to stop the child */
		signal(SIGHUP, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);

		if (flag & F_NOWAIT)
			setsid();
	}

	if (p == -1)
		perror("fork");
	return p;
}