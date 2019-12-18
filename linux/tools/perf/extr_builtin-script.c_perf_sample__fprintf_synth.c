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
struct perf_sample {int dummy; } ;
struct TYPE_3__ {int config; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  PERF_SYNTH_INTEL_CBR 133 
#define  PERF_SYNTH_INTEL_EXSTOP 132 
#define  PERF_SYNTH_INTEL_MWAIT 131 
#define  PERF_SYNTH_INTEL_PTWRITE 130 
#define  PERF_SYNTH_INTEL_PWRE 129 
#define  PERF_SYNTH_INTEL_PWRX 128 
 int perf_sample__fprintf_synth_cbr (struct perf_sample*,int /*<<< orphan*/ *) ; 
 int perf_sample__fprintf_synth_exstop (struct perf_sample*,int /*<<< orphan*/ *) ; 
 int perf_sample__fprintf_synth_mwait (struct perf_sample*,int /*<<< orphan*/ *) ; 
 int perf_sample__fprintf_synth_ptwrite (struct perf_sample*,int /*<<< orphan*/ *) ; 
 int perf_sample__fprintf_synth_pwre (struct perf_sample*,int /*<<< orphan*/ *) ; 
 int perf_sample__fprintf_synth_pwrx (struct perf_sample*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_sample__fprintf_synth(struct perf_sample *sample,
				      struct evsel *evsel, FILE *fp)
{
	switch (evsel->core.attr.config) {
	case PERF_SYNTH_INTEL_PTWRITE:
		return perf_sample__fprintf_synth_ptwrite(sample, fp);
	case PERF_SYNTH_INTEL_MWAIT:
		return perf_sample__fprintf_synth_mwait(sample, fp);
	case PERF_SYNTH_INTEL_PWRE:
		return perf_sample__fprintf_synth_pwre(sample, fp);
	case PERF_SYNTH_INTEL_EXSTOP:
		return perf_sample__fprintf_synth_exstop(sample, fp);
	case PERF_SYNTH_INTEL_PWRX:
		return perf_sample__fprintf_synth_pwrx(sample, fp);
	case PERF_SYNTH_INTEL_CBR:
		return perf_sample__fprintf_synth_cbr(sample, fp);
	default:
		break;
	}

	return 0;
}