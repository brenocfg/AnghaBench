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
typedef  int /*<<< orphan*/  u64 ;
struct perf_event_attr {scalar_t__ type; int /*<<< orphan*/  config; } ;
struct intel_pt {scalar_t__ pmu_type; } ;

/* Variables and functions */

__attribute__((used)) static bool intel_pt_get_config(struct intel_pt *pt,
				struct perf_event_attr *attr, u64 *config)
{
	if (attr->type == pt->pmu_type) {
		if (config)
			*config = attr->config;
		return true;
	}

	return false;
}