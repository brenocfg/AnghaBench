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
struct perf_pmu {int selectable; } ;
struct perf_event_attr {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_default_config (struct perf_pmu*) ; 
 struct perf_event_attr* zalloc (int) ; 

struct perf_event_attr *
intel_pt_pmu_default_config(struct perf_pmu *intel_pt_pmu)
{
	struct perf_event_attr *attr;

	attr = zalloc(sizeof(struct perf_event_attr));
	if (!attr)
		return NULL;

	attr->config = intel_pt_default_config(intel_pt_pmu);

	intel_pt_pmu->selectable = true;

	return attr;
}