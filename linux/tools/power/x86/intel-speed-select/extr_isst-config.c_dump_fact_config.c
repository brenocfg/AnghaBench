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
 int /*<<< orphan*/  dump_fact_config_for_cpu ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  for_each_online_package_in_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  for_each_online_target_cpu_in_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isst_ctdp_display_information_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isst_ctdp_display_information_start (int /*<<< orphan*/ ) ; 
 scalar_t__ max_target_cpus ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  stderr ; 
 int tdp_level ; 

__attribute__((used)) static void dump_fact_config(void)
{
	if (cmd_help) {
		fprintf(stderr,
			"Print complete Intel Speed Select Technology turbo frequency configuration for a TDP level. Other arguments are optional.\n");
		fprintf(stderr,
			"\tArguments: -l|--level : Specify tdp level\n");
		fprintf(stderr,
			"\tArguments: -b|--bucket : Bucket index to dump\n");
		fprintf(stderr,
			"\tArguments: -r|--trl-type : Specify trl type: sse|avx2|avx512\n");
		exit(0);
	}

	if (tdp_level == 0xff) {
		fprintf(outf, "Invalid command: specify tdp_level\n");
		exit(1);
	}

	isst_ctdp_display_information_start(outf);
	if (max_target_cpus)
		for_each_online_target_cpu_in_set(dump_fact_config_for_cpu,
						  NULL, NULL, NULL, NULL);
	else
		for_each_online_package_in_set(dump_fact_config_for_cpu, NULL,
					       NULL, NULL, NULL);
	isst_ctdp_display_information_end(outf);
}