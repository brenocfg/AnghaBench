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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int sched_next_online (int,int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_parallel(unsigned int tasks, void (*fn)(int i, void *data),
			 void *data)
{
	int next_sched_cpu = 0;
	pid_t pid[tasks];
	int i;

	for (i = 0; i < tasks; i++) {
		pid[i] = fork();
		if (pid[i] == 0) {
			next_sched_cpu = sched_next_online(0, next_sched_cpu);
			fn(i, data);
			exit(0);
		} else if (pid[i] == -1) {
			printf("couldn't spawn #%d process\n", i);
			exit(1);
		}
		/* It is mostly redundant and just allow the parent
		 * process to update next_shced_cpu for the next child
		 * process
		 */
		next_sched_cpu = sched_next_online(pid[i], next_sched_cpu);
	}
	for (i = 0; i < tasks; i++) {
		int status;

		assert(waitpid(pid[i], &status, 0) == pid[i]);
		assert(status == 0);
	}
}