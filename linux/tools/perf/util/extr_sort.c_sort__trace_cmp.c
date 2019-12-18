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
struct hist_entry {int /*<<< orphan*/ * trace_output; int /*<<< orphan*/  hists; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ PERF_TYPE_TRACEPOINT ; 
 void* get_trace_output (struct hist_entry*) ; 
 struct evsel* hists_to_evsel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t
sort__trace_cmp(struct hist_entry *left, struct hist_entry *right)
{
	struct evsel *evsel;

	evsel = hists_to_evsel(left->hists);
	if (evsel->core.attr.type != PERF_TYPE_TRACEPOINT)
		return 0;

	if (left->trace_output == NULL)
		left->trace_output = get_trace_output(left);
	if (right->trace_output == NULL)
		right->trace_output = get_trace_output(right);

	return strcmp(right->trace_output, left->trace_output);
}