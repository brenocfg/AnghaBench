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
struct stat {int dummy; } ;

/* Variables and functions */
 int base_cpu ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ system (char*) ; 

void probe_dev_msr(void)
{
	struct stat sb;
	char pathname[32];

	sprintf(pathname, "/dev/cpu/%d/msr", base_cpu);
	if (stat(pathname, &sb))
		if (system("/sbin/modprobe msr > /dev/null 2>&1"))
			err(-5, "no /dev/cpu/0/msr, Try \"# modprobe msr\" ");
}