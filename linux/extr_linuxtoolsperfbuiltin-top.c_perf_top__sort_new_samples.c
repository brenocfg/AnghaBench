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
struct perf_top {int /*<<< orphan*/  hide_kernel_symbols; int /*<<< orphan*/  hide_user_symbols; scalar_t__ zero; TYPE_1__* evlist; struct perf_evsel* sym_evsel; } ;
struct perf_evsel {int dummy; } ;
struct hists {int dummy; } ;
struct TYPE_2__ {scalar_t__ enabled; struct perf_evsel* selected; } ;

/* Variables and functions */
 struct hists* evsel__hists (struct perf_evsel*) ; 
 int /*<<< orphan*/  hists__collapse_resort (struct hists*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hists__decay_entries (struct hists*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__delete_entries (struct hists*) ; 
 int /*<<< orphan*/  perf_evsel__output_resort (struct perf_evsel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_top__reset_sample_counters (struct perf_top*) ; 

__attribute__((used)) static void perf_top__sort_new_samples(void *arg)
{
	struct perf_top *t = arg;
	struct perf_evsel *evsel = t->sym_evsel;
	struct hists *hists;

	perf_top__reset_sample_counters(t);

	if (t->evlist->selected != NULL)
		t->sym_evsel = t->evlist->selected;

	hists = evsel__hists(evsel);

	if (t->evlist->enabled) {
		if (t->zero) {
			hists__delete_entries(hists);
		} else {
			hists__decay_entries(hists, t->hide_user_symbols,
					     t->hide_kernel_symbols);
		}
	}

	hists__collapse_resort(hists, NULL);
	perf_evsel__output_resort(evsel, NULL);
}