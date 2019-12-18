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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int MAX_CPUS ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_CONF ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_total_cpus(void)
{
	int nr_cpus = (int)sysconf(_SC_NPROCESSORS_CONF);

	if (nr_cpus <= 0) {
		pr_err("Could not read cpus\n");
		goto error;
	} else if (nr_cpus > MAX_CPUS) {
		pr_err("Exceed max cpus(%d)\n", (int)MAX_CPUS);
		goto error;
	}

	return nr_cpus;

error:
	exit(EXIT_FAILURE);
}