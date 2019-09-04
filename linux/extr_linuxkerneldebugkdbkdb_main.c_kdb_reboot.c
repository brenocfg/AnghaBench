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
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  emergency_restart () ; 
 int /*<<< orphan*/  kdb_printf (char*) ; 

__attribute__((used)) static int kdb_reboot(int argc, const char **argv)
{
	emergency_restart();
	kdb_printf("Hmm, kdb_reboot did not reboot, spinning here\n");
	while (1)
		cpu_relax();
	/* NOTREACHED */
	return 0;
}