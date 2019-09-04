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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 scalar_t__ cg_write (char const*,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int getpid () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int cg_run_nowait(const char *cgroup,
		  int (*fn)(const char *cgroup, void *arg),
		  void *arg)
{
	int pid;

	pid = fork();
	if (pid == 0) {
		char buf[64];

		snprintf(buf, sizeof(buf), "%d", getpid());
		if (cg_write(cgroup, "cgroup.procs", buf))
			exit(EXIT_FAILURE);
		exit(fn(cgroup, arg));
	}

	return pid;
}