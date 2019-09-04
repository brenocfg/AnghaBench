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
struct perf_sample {int cpu; } ;
struct TYPE_2__ {int sample_type; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct ctf_writer {int stream_cnt; } ;

/* Variables and functions */
 int PERF_SAMPLE_CPU ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static int get_sample_cpu(struct ctf_writer *cw, struct perf_sample *sample,
			  struct perf_evsel *evsel)
{
	int cpu = 0;

	if (evsel->attr.sample_type & PERF_SAMPLE_CPU)
		cpu = sample->cpu;

	if (cpu > cw->stream_cnt) {
		pr_err("Event was recorded for CPU %d, limit is at %d.\n",
			cpu, cw->stream_cnt);
		cpu = 0;
	}

	return cpu;
}