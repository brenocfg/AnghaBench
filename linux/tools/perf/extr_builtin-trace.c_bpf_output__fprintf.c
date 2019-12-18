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
struct trace {int /*<<< orphan*/  nr_events_printed; int /*<<< orphan*/  output; } ;
struct perf_sample {int /*<<< orphan*/  raw_size; int /*<<< orphan*/  raw_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  binary__fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_output__printer ; 

__attribute__((used)) static void bpf_output__fprintf(struct trace *trace,
				struct perf_sample *sample)
{
	binary__fprintf(sample->raw_data, sample->raw_size, 8,
			bpf_output__printer, NULL, trace->output);
	++trace->nr_events_printed;
}