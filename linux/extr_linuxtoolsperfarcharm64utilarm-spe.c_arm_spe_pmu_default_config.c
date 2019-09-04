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
struct perf_pmu {int selectable; int is_uncore; } ;
struct perf_event_attr {int sample_period; } ;

/* Variables and functions */
 int perf_pmu__scan_file (struct perf_pmu*,char*,char*,int*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct perf_event_attr* zalloc (int) ; 

struct perf_event_attr
*arm_spe_pmu_default_config(struct perf_pmu *arm_spe_pmu)
{
	struct perf_event_attr *attr;

	attr = zalloc(sizeof(struct perf_event_attr));
	if (!attr) {
		pr_err("arm_spe default config cannot allocate a perf_event_attr\n");
		return NULL;
	}

	/*
	 * If kernel driver doesn't advertise a minimum,
	 * use max allowable by PMSIDR_EL1.INTERVAL
	 */
	if (perf_pmu__scan_file(arm_spe_pmu, "caps/min_interval", "%llu",
				  &attr->sample_period) != 1) {
		pr_debug("arm_spe driver doesn't advertise a min. interval. Using 4096\n");
		attr->sample_period = 4096;
	}

	arm_spe_pmu->selectable = true;
	arm_spe_pmu->is_uncore = false;

	return attr;
}