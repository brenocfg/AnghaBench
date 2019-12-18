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
 scalar_t__ cmd_help ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_online_target_cpu_in_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_clos_assoc_for_cpu ; 
 int /*<<< orphan*/  isst_ctdp_display_information_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isst_ctdp_display_information_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_target_cpus ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void get_clos_assoc(void)
{
	if (cmd_help) {
		fprintf(stderr, "Get associate clos id to a CPU\n");
		fprintf(stderr, "\tSpecify targeted cpu id with [--cpu|-c]\n");
		exit(0);
	}

	if (!max_target_cpus) {
		fprintf(stderr,
			"Invalid target cpu. Specify with [-c|--cpu]\n");
		exit(0);
	}

	isst_ctdp_display_information_start(outf);
	for_each_online_target_cpu_in_set(get_clos_assoc_for_cpu, NULL,
					  NULL, NULL, NULL);
	isst_ctdp_display_information_end(outf);
}