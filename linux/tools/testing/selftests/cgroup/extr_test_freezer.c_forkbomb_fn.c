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
 int /*<<< orphan*/  fork () ; 
 int getppid () ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int forkbomb_fn(const char *cgroup, void *arg)
{
	int ppid;

	fork();
	fork();

	ppid = getppid();

	while (getppid() == ppid)
		usleep(1000);

	return getppid() == ppid;
}