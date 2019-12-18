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
 int /*<<< orphan*/  PR_TSC_ENABLE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtsc () ; 
 scalar_t__ should_segv ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void sigsegv_cb(int sig)
{
	if (!should_segv)
	{
		fprintf(stderr, "FATAL ERROR, rdtsc() failed while enabled\n");
		exit(0);
	}
	if (prctl(PR_SET_TSC, PR_TSC_ENABLE) < 0)
	{
		perror("prctl");
		exit(0);
	}
	should_segv = 0;

	rdtsc();
}