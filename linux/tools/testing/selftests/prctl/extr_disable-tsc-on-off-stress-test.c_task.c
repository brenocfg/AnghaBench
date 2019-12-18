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
 int /*<<< orphan*/  PR_SET_TSC ; 
 int /*<<< orphan*/  PR_TSC_SIGSEGV ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtsc () ; 
 int should_segv ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsegv_cb ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void task(void)
{
	signal(SIGSEGV, sigsegv_cb);
	alarm(10);
	for(;;)
	{
		rdtsc();
		if (should_segv)
		{
			fprintf(stderr, "FATAL ERROR, rdtsc() succeeded while disabled\n");
			exit(0);
		}
		if (prctl(PR_SET_TSC, PR_TSC_SIGSEGV) < 0)
		{
			perror("prctl");
			exit(0);
		}
		should_segv = 1;
	}
}