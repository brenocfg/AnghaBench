#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 scalar_t__ csv_output ; 
 char* csv_sep ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 double rel_stddev_stats (double,double) ; 
 TYPE_1__ stat_config ; 

__attribute__((used)) static void print_noise_pct(double total, double avg)
{
	double pct = rel_stddev_stats(total, avg);

	if (csv_output)
		fprintf(stat_config.output, "%s%.2f%%", csv_sep, pct);
	else if (pct)
		fprintf(stat_config.output, "  ( +-%6.2f%% )", pct);
}