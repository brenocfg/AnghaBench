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
typedef  scalar_t__ u64 ;
struct hist_entry {TYPE_1__* hists; int /*<<< orphan*/  filtered; } ;
struct TYPE_4__ {int /*<<< orphan*/  use_callchain; } ;
struct TYPE_3__ {int /*<<< orphan*/  callchain_non_filtered_period; int /*<<< orphan*/  callchain_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  hist_entry__has_callchains (struct hist_entry*) ; 
 TYPE_2__ symbol_conf ; 

__attribute__((used)) static void hist_entry__add_callchain_period(struct hist_entry *he, u64 period)
{
	if (!hist_entry__has_callchains(he) || !symbol_conf.use_callchain)
		return;

	he->hists->callchain_period += period;
	if (!he->filtered)
		he->hists->callchain_non_filtered_period += period;
}