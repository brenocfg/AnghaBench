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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF_D (int) ; 
 int F_NOWAIT ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  oldsighup ; 
 int /*<<< orphan*/  oldsigtstp ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int join(pid_t p, uchar flag)
{
	int status = 0xFFFF;

	if (!(flag & F_NOWAIT)) {
		/* wait for the child to exit */
		do {
		} while (waitpid(p, &status, 0) == -1);

		if (WIFEXITED(status)) {
			status = WEXITSTATUS(status);
			DPRINTF_D(status);
		}
	}

	/* restore parent's signal handling */
	signal(SIGHUP, oldsighup);
	signal(SIGTSTP, oldsigtstp);

	return status;
}