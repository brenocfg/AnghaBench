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
struct TYPE_3__ {int /*<<< orphan*/  total_non_filtered_period; } ;
struct hists {TYPE_1__ stats; int /*<<< orphan*/  nr_non_filtered_entries; } ;
struct TYPE_4__ {scalar_t__ period; } ;
struct hist_entry {TYPE_2__ stat; } ;

/* Variables and functions */

__attribute__((used)) static void hists__inc_filter_stats(struct hists *hists, struct hist_entry *h)
{
	hists->nr_non_filtered_entries++;
	hists->stats.total_non_filtered_period += h->stat.period;
}