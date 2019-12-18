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
struct perf_stat_config {char* csv_sep; int /*<<< orphan*/  output; scalar_t__ csv_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 double rel_stddev_stats (double,double) ; 

__attribute__((used)) static void print_noise_pct(struct perf_stat_config *config,
			    double total, double avg)
{
	double pct = rel_stddev_stats(total, avg);

	if (config->csv_output)
		fprintf(config->output, "%s%.2f%%", config->csv_sep, pct);
	else if (pct)
		fprintf(config->output, "  ( +-%6.2f%% )", pct);
}