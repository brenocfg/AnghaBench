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
struct ui_progress {int dummy; } ;
struct evsel {int dummy; } ;
typedef  int /*<<< orphan*/  hists__resort_cb_t ;
struct TYPE_2__ {int use_callchain; int show_branchflag_count; int /*<<< orphan*/  show_ref_callgraph; } ;

/* Variables and functions */
 int evsel__has_callchain (struct evsel*) ; 
 int /*<<< orphan*/  evsel__hists (struct evsel*) ; 
 int /*<<< orphan*/  output_resort (int /*<<< orphan*/ ,struct ui_progress*,int,int /*<<< orphan*/ ,void*) ; 
 TYPE_1__ symbol_conf ; 

void perf_evsel__output_resort_cb(struct evsel *evsel, struct ui_progress *prog,
				  hists__resort_cb_t cb, void *cb_arg)
{
	bool use_callchain;

	if (evsel && symbol_conf.use_callchain && !symbol_conf.show_ref_callgraph)
		use_callchain = evsel__has_callchain(evsel);
	else
		use_callchain = symbol_conf.use_callchain;

	use_callchain |= symbol_conf.show_branchflag_count;

	output_resort(evsel__hists(evsel), prog, use_callchain, cb, cb_arg);
}