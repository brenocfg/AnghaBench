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
struct perf_synth_intel_exstop {int ip; } ;
struct perf_sample {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fprintf (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ perf_sample__bad_synth_size (struct perf_sample*,struct perf_synth_intel_exstop) ; 
 int perf_sample__fprintf_pt_spacing (int,int /*<<< orphan*/ *) ; 
 struct perf_synth_intel_exstop* perf_sample__synth_ptr (struct perf_sample*) ; 

__attribute__((used)) static int perf_sample__fprintf_synth_exstop(struct perf_sample *sample, FILE *fp)
{
	struct perf_synth_intel_exstop *data = perf_sample__synth_ptr(sample);
	int len;

	if (perf_sample__bad_synth_size(sample, *data))
		return 0;

	len = fprintf(fp, " IP: %u ", data->ip);
	return len + perf_sample__fprintf_pt_spacing(len, fp);
}