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
struct TYPE_2__ {scalar_t__ type; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct hist_entry {int /*<<< orphan*/ * trace_output; int /*<<< orphan*/  hists; } ;

/* Variables and functions */
 scalar_t__ PERF_TYPE_TRACEPOINT ; 
 int /*<<< orphan*/ * get_trace_output (struct hist_entry*) ; 
 struct perf_evsel* hists_to_evsel (int /*<<< orphan*/ ) ; 
 int repsep_snprintf (char*,size_t,char*,unsigned int,int /*<<< orphan*/ *) ; 
 int scnprintf (char*,size_t,char*,unsigned int,char*) ; 

__attribute__((used)) static int hist_entry__trace_snprintf(struct hist_entry *he, char *bf,
				    size_t size, unsigned int width)
{
	struct perf_evsel *evsel;

	evsel = hists_to_evsel(he->hists);
	if (evsel->attr.type != PERF_TYPE_TRACEPOINT)
		return scnprintf(bf, size, "%-.*s", width, "N/A");

	if (he->trace_output == NULL)
		he->trace_output = get_trace_output(he);
	return repsep_snprintf(bf, size, "%-.*s", width, he->trace_output);
}