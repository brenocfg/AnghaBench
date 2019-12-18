#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct perf_sample {int period; struct ip_callchain* callchain; int /*<<< orphan*/  ip; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; int /*<<< orphan*/  cpumode; } ;
struct machine {int dummy; } ;
struct ip_callchain {int dummy; } ;
struct hists {int dummy; } ;
struct hist_entry_iter {int hide_unresolved; int /*<<< orphan*/ * ops; struct perf_sample* sample; struct evsel* evsel; } ;
struct evsel {int dummy; } ;
struct addr_location {int /*<<< orphan*/  sym; int /*<<< orphan*/  map; int /*<<< orphan*/  thread; } ;
struct TYPE_5__ {int /*<<< orphan*/  sym; int /*<<< orphan*/  map; int /*<<< orphan*/  thread; int /*<<< orphan*/  ip; int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {scalar_t__ cumulate_callchain; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 int TEST_FAIL ; 
 int TEST_OK ; 
 int /*<<< orphan*/  addr_location__put (struct addr_location*) ; 
 scalar_t__* fake_callchains ; 
 TYPE_2__* fake_samples ; 
 scalar_t__ hist_entry_iter__add (struct hist_entry_iter*,struct addr_location*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hist_iter_cumulative ; 
 int /*<<< orphan*/  hist_iter_normal ; 
 struct evsel* hists_to_evsel (struct hists*) ; 
 scalar_t__ machine__resolve (struct machine*,struct addr_location*,struct perf_sample*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  sysctl_perf_event_max_stack ; 

__attribute__((used)) static int add_hist_entries(struct hists *hists, struct machine *machine)
{
	struct addr_location al;
	struct evsel *evsel = hists_to_evsel(hists);
	struct perf_sample sample = { .period = 1000, };
	size_t i;

	for (i = 0; i < ARRAY_SIZE(fake_samples); i++) {
		struct hist_entry_iter iter = {
			.evsel = evsel,
			.sample	= &sample,
			.hide_unresolved = false,
		};

		if (symbol_conf.cumulate_callchain)
			iter.ops = &hist_iter_cumulative;
		else
			iter.ops = &hist_iter_normal;

		sample.cpumode = PERF_RECORD_MISC_USER;
		sample.pid = fake_samples[i].pid;
		sample.tid = fake_samples[i].pid;
		sample.ip = fake_samples[i].ip;
		sample.callchain = (struct ip_callchain *)fake_callchains[i];

		if (machine__resolve(machine, &al, &sample) < 0)
			goto out;

		if (hist_entry_iter__add(&iter, &al, sysctl_perf_event_max_stack,
					 NULL) < 0) {
			addr_location__put(&al);
			goto out;
		}

		fake_samples[i].thread = al.thread;
		fake_samples[i].map = al.map;
		fake_samples[i].sym = al.sym;
	}

	return TEST_OK;

out:
	pr_debug("Not enough memory for adding a hist entry\n");
	return TEST_FAIL;
}