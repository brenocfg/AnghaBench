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
struct perf_sample {int dummy; } ;
struct hists {int dummy; } ;
struct hist_entry_iter {int /*<<< orphan*/  curr; struct hist_entry* he; int /*<<< orphan*/  parent; struct hist_entry** priv; struct perf_sample* sample; struct evsel* evsel; } ;
struct hist_entry {int /*<<< orphan*/  filtered; } ;
struct evsel {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  callchain_cursor ; 
 int /*<<< orphan*/  callchain_cursor_commit (int /*<<< orphan*/ *) ; 
 struct hists* evsel__hists (struct evsel*) ; 
 int /*<<< orphan*/  hist_entry__append_callchain (struct hist_entry*,struct perf_sample*) ; 
 struct hist_entry* hists__add_entry (struct hists*,struct addr_location*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct perf_sample*,int) ; 
 int /*<<< orphan*/  hists__inc_nr_samples (struct hists*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iter_add_single_cumulative_entry(struct hist_entry_iter *iter,
				 struct addr_location *al)
{
	struct evsel *evsel = iter->evsel;
	struct hists *hists = evsel__hists(evsel);
	struct perf_sample *sample = iter->sample;
	struct hist_entry **he_cache = iter->priv;
	struct hist_entry *he;
	int err = 0;

	he = hists__add_entry(hists, al, iter->parent, NULL, NULL,
			      sample, true);
	if (he == NULL)
		return -ENOMEM;

	iter->he = he;
	he_cache[iter->curr++] = he;

	hist_entry__append_callchain(he, sample);

	/*
	 * We need to re-initialize the cursor since callchain_append()
	 * advanced the cursor to the end.
	 */
	callchain_cursor_commit(&callchain_cursor);

	hists__inc_nr_samples(hists, he->filtered);

	return err;
}