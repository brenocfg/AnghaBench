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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PR_SET_PDEATHSIG ; 
 int /*<<< orphan*/  SIGKILL ; 
 int getpid () ; 
 int getppid () ; 
 int kill (int,int /*<<< orphan*/ ) ; 
 int prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int set_death_signal(void)
{
	int ret;
	pid_t ppid;

	ret = prctl(PR_SET_PDEATHSIG, SIGKILL, 0, 0, 0);

	/* Check whether we have been orphaned. */
	ppid = getppid();
	if (ppid == 1) {
		pid_t self;

		self = getpid();
		ret = kill(self, SIGKILL);
	}

	if (ret < 0)
		return -1;

	return 0;
}