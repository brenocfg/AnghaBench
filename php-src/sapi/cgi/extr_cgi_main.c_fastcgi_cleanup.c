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

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int exit_signal ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_term ; 
 scalar_t__ parent ; 
 scalar_t__ parent_waiting ; 
 int /*<<< orphan*/  pgroup ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void fastcgi_cleanup(int signal)
{
#ifdef DEBUG_FASTCGI
	fprintf(stderr, "FastCGI shutdown, pid %d\n", getpid());
#endif

	sigaction(SIGTERM, &old_term, 0);

	/* Kill all the processes in our process group */
	kill(-pgroup, SIGTERM);

	if (parent && parent_waiting) {
		exit_signal = 1;
	} else {
		exit(0);
	}
}