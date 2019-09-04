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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int NR_CHILDREN ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int bind_to_cpu (int) ; 
 int /*<<< orphan*/  cycles_child () ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int pick_online_cpu () ; 
 int /*<<< orphan*/  sleep (int) ; 
 int wait_for_child (scalar_t__) ; 

int multi_ebb_procs(void)
{
	pid_t pids[NR_CHILDREN];
	int cpu, rc, i;

	SKIP_IF(!ebb_is_supported());

	cpu = pick_online_cpu();
	FAIL_IF(cpu < 0);
	FAIL_IF(bind_to_cpu(cpu));

	for (i = 0; i < NR_CHILDREN; i++) {
		pids[i] = fork();
		if (pids[i] == 0)
			exit(cycles_child());
	}

	/* Have them all run for "a while" */
	sleep(10);

	rc = 0;
	for (i = 0; i < NR_CHILDREN; i++) {
		/* Tell them to stop */
		kill(pids[i], SIGINT);
		/* And wait */
		rc |= wait_for_child(pids[i]);
	}

	return rc;
}