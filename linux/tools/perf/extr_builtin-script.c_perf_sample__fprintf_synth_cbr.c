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
struct perf_synth_intel_cbr {int cbr; int max_nonturbo; int /*<<< orphan*/  freq; } ;
struct perf_sample {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fprintf (int /*<<< orphan*/ *,char*,unsigned int,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_sample__bad_synth_size (struct perf_sample*,struct perf_synth_intel_cbr) ; 
 int perf_sample__fprintf_pt_spacing (int,int /*<<< orphan*/ *) ; 
 struct perf_synth_intel_cbr* perf_sample__synth_ptr (struct perf_sample*) ; 

__attribute__((used)) static int perf_sample__fprintf_synth_cbr(struct perf_sample *sample, FILE *fp)
{
	struct perf_synth_intel_cbr *data = perf_sample__synth_ptr(sample);
	unsigned int percent, freq;
	int len;

	if (perf_sample__bad_synth_size(sample, *data))
		return 0;

	freq = (le32_to_cpu(data->freq) + 500) / 1000;
	len = fprintf(fp, " cbr: %2u freq: %4u MHz ", data->cbr, freq);
	if (data->max_nonturbo) {
		percent = (5 + (1000 * data->cbr) / data->max_nonturbo) / 10;
		len += fprintf(fp, "(%3u%%) ", percent);
	}
	return len + perf_sample__fprintf_pt_spacing(len, fp);
}