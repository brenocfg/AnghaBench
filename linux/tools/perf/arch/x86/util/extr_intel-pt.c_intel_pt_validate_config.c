#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_pmu {int dummy; } ;
struct TYPE_3__ {int config; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;

/* Variables and functions */
 int intel_pt_val_config_term (struct perf_pmu*,char*,char*,char*,int) ; 
 int perf_pmu__scan_file (struct perf_pmu*,char*,char*,char*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static int intel_pt_validate_config(struct perf_pmu *intel_pt_pmu,
				    struct evsel *evsel)
{
	int err;
	char c;

	if (!evsel)
		return 0;

	/*
	 * If supported, force pass-through config term (pt=1) even if user
	 * sets pt=0, which avoids senseless kernel errors.
	 */
	if (perf_pmu__scan_file(intel_pt_pmu, "format/pt", "%c", &c) == 1 &&
	    !(evsel->core.attr.config & 1)) {
		pr_warning("pt=0 doesn't make sense, forcing pt=1\n");
		evsel->core.attr.config |= 1;
	}

	err = intel_pt_val_config_term(intel_pt_pmu, "caps/cycle_thresholds",
				       "cyc_thresh", "caps/psb_cyc",
				       evsel->core.attr.config);
	if (err)
		return err;

	err = intel_pt_val_config_term(intel_pt_pmu, "caps/mtc_periods",
				       "mtc_period", "caps/mtc",
				       evsel->core.attr.config);
	if (err)
		return err;

	return intel_pt_val_config_term(intel_pt_pmu, "caps/psb_periods",
					"psb_period", "caps/psb_cyc",
					evsel->core.attr.config);
}