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
 int ENERGY_PERF_BIAS_BALANCE_PERFORMANCE ; 
 int ENERGY_PERF_BIAS_BALANCE_POWERSAVE ; 
 int ENERGY_PERF_BIAS_NORMAL ; 
 int ENERGY_PERF_BIAS_PERFORMANCE ; 
 int ENERGY_PERF_BIAS_POWERSAVE ; 
#define  OPTARG_BALANCE_PERFORMANCE 132 
#define  OPTARG_BALANCE_POWER 131 
#define  OPTARG_NORMAL 130 
#define  OPTARG_PERFORMANCE 129 
#define  OPTARG_POWER 128 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  has_epb ; 
 int update_epb ; 

int parse_cmdline_epb(int i)
{
	if (!has_epb)
		errx(1, "EPB not enabled on this platform");

	update_epb = 1;

	switch (i) {
	case OPTARG_POWER:
		return ENERGY_PERF_BIAS_POWERSAVE;
	case OPTARG_BALANCE_POWER:
		return ENERGY_PERF_BIAS_BALANCE_POWERSAVE;
	case OPTARG_NORMAL:
		return ENERGY_PERF_BIAS_NORMAL;
	case OPTARG_BALANCE_PERFORMANCE:
		return ENERGY_PERF_BIAS_BALANCE_PERFORMANCE;
	case OPTARG_PERFORMANCE:
		return ENERGY_PERF_BIAS_PERFORMANCE;
	}
	if (i < 0 || i > ENERGY_PERF_BIAS_POWERSAVE)
		errx(1, "--epb must be from 0 to 15");
	return i;
}