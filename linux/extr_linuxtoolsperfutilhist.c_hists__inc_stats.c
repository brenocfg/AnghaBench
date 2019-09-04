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
struct TYPE_3__ {int /*<<< orphan*/  total_period; } ;
struct hists {TYPE_1__ stats; int /*<<< orphan*/  nr_entries; } ;
struct TYPE_4__ {scalar_t__ period; } ;
struct hist_entry {TYPE_2__ stat; int /*<<< orphan*/  filtered; } ;

/* Variables and functions */
 int /*<<< orphan*/  hists__inc_filter_stats (struct hists*,struct hist_entry*) ; 

void hists__inc_stats(struct hists *hists, struct hist_entry *h)
{
	if (!h->filtered)
		hists__inc_filter_stats(hists, h);

	hists->nr_entries++;
	hists->stats.total_period += h->stat.period;
}