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
typedef  int /*<<< orphan*/  pidbuf ;

/* Variables and functions */
 int cg_write (char const*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int cg_enter(const char *cgroup, int pid)
{
	char pidbuf[64];

	snprintf(pidbuf, sizeof(pidbuf), "%d", pid);
	return cg_write(cgroup, "cgroup.procs", pidbuf);
}