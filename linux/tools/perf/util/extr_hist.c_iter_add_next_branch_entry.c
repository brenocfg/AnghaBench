#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct perf_sample {int period; int weight; } ;
struct hists {int dummy; } ;
struct hist_entry_iter {int curr; struct hist_entry* he; int /*<<< orphan*/  parent; scalar_t__ hide_unresolved; struct branch_info* priv; struct perf_sample* sample; struct evsel* evsel; } ;
struct hist_entry {int /*<<< orphan*/  filtered; } ;
struct evsel {int dummy; } ;
struct TYPE_6__ {int cycles; } ;
struct TYPE_5__ {scalar_t__ sym; } ;
struct TYPE_4__ {scalar_t__ sym; } ;
struct branch_info {TYPE_3__ flags; TYPE_2__ to; TYPE_1__ from; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct hists* evsel__hists (struct evsel*) ; 
 struct hist_entry* hists__add_entry (struct hists*,struct addr_location*,int /*<<< orphan*/ ,struct branch_info*,int /*<<< orphan*/ *,struct perf_sample*,int) ; 
 int /*<<< orphan*/  hists__inc_nr_samples (struct hists*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iter_add_next_branch_entry(struct hist_entry_iter *iter, struct addr_location *al)
{
	struct branch_info *bi;
	struct evsel *evsel = iter->evsel;
	struct hists *hists = evsel__hists(evsel);
	struct perf_sample *sample = iter->sample;
	struct hist_entry *he = NULL;
	int i = iter->curr;
	int err = 0;

	bi = iter->priv;

	if (iter->hide_unresolved && !(bi[i].from.sym && bi[i].to.sym))
		goto out;

	/*
	 * The report shows the percentage of total branches captured
	 * and not events sampled. Thus we use a pseudo period of 1.
	 */
	sample->period = 1;
	sample->weight = bi->flags.cycles ? bi->flags.cycles : 1;

	he = hists__add_entry(hists, al, iter->parent, &bi[i], NULL,
			      sample, true);
	if (he == NULL)
		return -ENOMEM;

	hists__inc_nr_samples(hists, he->filtered);

out:
	iter->he = he;
	iter->curr++;
	return err;
}