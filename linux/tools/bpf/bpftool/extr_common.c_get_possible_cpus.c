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
 int libbpf_num_possible_cpus () ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 

unsigned int get_possible_cpus(void)
{
	int cpus = libbpf_num_possible_cpus();

	if (cpus < 0) {
		p_err("Can't get # of possible cpus: %s", strerror(-cpus));
		exit(-1);
	}
	return cpus;
}