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
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_process_on(void *(*fn)(void *), void *arg, unsigned long cpu)
{
	int pid;
	cpu_set_t cpuset;

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}

	if (pid)
		return;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	if (sched_setaffinity(0, sizeof(cpuset), &cpuset)) {
		perror("sched_setaffinity");
		exit(1);
	}

	fn(arg);

	exit(0);
}