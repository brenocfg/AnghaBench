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
struct hist_entry_iter {struct hist_entry* he; int /*<<< orphan*/  parent; struct perf_sample* sample; struct evsel* evsel; } ;
struct hist_entry {int dummy; } ;
struct evsel {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  evsel__hists (struct evsel*) ; 
 struct hist_entry* hists__add_entry (int /*<<< orphan*/ ,struct addr_location*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct perf_sample*,int) ; 

__attribute__((used)) static int
iter_add_single_normal_entry(struct hist_entry_iter *iter, struct addr_location *al)
{
	struct evsel *evsel = iter->evsel;
	struct perf_sample *sample = iter->sample;
	struct hist_entry *he;

	he = hists__add_entry(evsel__hists(evsel), al, iter->parent, NULL, NULL,
			      sample, true);
	if (he == NULL)
		return -ENOMEM;

	iter->he = he;
	return 0;
}