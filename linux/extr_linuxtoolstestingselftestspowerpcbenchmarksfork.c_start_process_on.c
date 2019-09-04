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
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  set_cpu (int) ; 

__attribute__((used)) static void start_process_on(void *(*fn)(void *), void *arg, int cpu)
{
	int pid;

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}

	if (pid)
		return;

	set_cpu(cpu);

	fn(arg);

	exit(0);
}