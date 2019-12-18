#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int branch_stack; } ;
struct perf_top {TYPE_1__ record_opts; } ;
struct hist_entry_iter {TYPE_2__* sample; struct evsel* evsel; struct hist_entry* he; } ;
struct hist_entry {int dummy; } ;
struct evsel {int dummy; } ;
struct addr_location {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {scalar_t__ sym; } ;
struct TYPE_6__ {int /*<<< orphan*/  branch_stack; } ;

/* Variables and functions */
 int PERF_SAMPLE_BRANCH_ANY ; 
 int /*<<< orphan*/  hist__account_cycles (int /*<<< orphan*/ ,struct addr_location*,TYPE_2__*,int) ; 
 TYPE_3__ perf_hpp_list ; 
 int /*<<< orphan*/  perf_top__record_precise_ip (struct perf_top*,struct hist_entry*,TYPE_2__*,struct evsel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hist_iter__top_callback(struct hist_entry_iter *iter,
				   struct addr_location *al, bool single,
				   void *arg)
{
	struct perf_top *top = arg;
	struct hist_entry *he = iter->he;
	struct evsel *evsel = iter->evsel;

	if (perf_hpp_list.sym && single)
		perf_top__record_precise_ip(top, he, iter->sample, evsel, al->addr);

	hist__account_cycles(iter->sample->branch_stack, al, iter->sample,
		     !(top->record_opts.branch_stack & PERF_SAMPLE_BRANCH_ANY));
	return 0;
}