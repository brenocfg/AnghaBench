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
typedef  int u64 ;
struct perf_sample {int weight; int period; } ;
struct mem_info {int dummy; } ;
struct hists {int dummy; } ;
struct hist_entry_iter {struct hist_entry* he; int /*<<< orphan*/  parent; struct perf_sample* sample; int /*<<< orphan*/  evsel; struct mem_info* priv; } ;
struct hist_entry {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct hists* evsel__hists (int /*<<< orphan*/ ) ; 
 struct hist_entry* hists__add_entry (struct hists*,struct addr_location*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mem_info*,struct perf_sample*,int) ; 

__attribute__((used)) static int
iter_add_single_mem_entry(struct hist_entry_iter *iter, struct addr_location *al)
{
	u64 cost;
	struct mem_info *mi = iter->priv;
	struct hists *hists = evsel__hists(iter->evsel);
	struct perf_sample *sample = iter->sample;
	struct hist_entry *he;

	if (mi == NULL)
		return -EINVAL;

	cost = sample->weight;
	if (!cost)
		cost = 1;

	/*
	 * must pass period=weight in order to get the correct
	 * sorting from hists__collapse_resort() which is solely
	 * based on periods. We want sorting be done on nr_events * weight
	 * and this is indirectly achieved by passing period=weight here
	 * and the he_stat__add_period() function.
	 */
	sample->period = cost;

	he = hists__add_entry(hists, al, iter->parent, NULL, mi,
			      sample, true);
	if (!he)
		return -ENOMEM;

	iter->he = he;
	return 0;
}