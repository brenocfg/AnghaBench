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
struct trace {int /*<<< orphan*/  output; } ;
struct perf_sample {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bt_stop_list; } ;

/* Variables and functions */
 unsigned int EVSEL__PRINT_DSO ; 
 unsigned int EVSEL__PRINT_SYM ; 
 unsigned int EVSEL__PRINT_UNKNOWN_AS_ADDR ; 
 int /*<<< orphan*/  callchain_cursor ; 
 int sample__fprintf_callchain (struct perf_sample*,int,unsigned int const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int trace__fprintf_callchain(struct trace *trace, struct perf_sample *sample)
{
	/* TODO: user-configurable print_opts */
	const unsigned int print_opts = EVSEL__PRINT_SYM |
				        EVSEL__PRINT_DSO |
				        EVSEL__PRINT_UNKNOWN_AS_ADDR;

	return sample__fprintf_callchain(sample, 38, print_opts, &callchain_cursor, symbol_conf.bt_stop_list, trace->output);
}