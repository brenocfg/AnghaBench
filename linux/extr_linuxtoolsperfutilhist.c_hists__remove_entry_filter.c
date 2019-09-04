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
struct TYPE_5__ {int /*<<< orphan*/  nr_non_filtered_samples; } ;
struct hists {TYPE_1__ stats; } ;
struct TYPE_7__ {scalar_t__ nr_events; } ;
struct hist_entry {int filtered; int unfolded; int has_no_entry; TYPE_3__ stat; scalar_t__ nr_rows; scalar_t__ row_offset; struct hist_entry* parent_he; } ;
typedef  enum hist_filter { ____Placeholder_hist_filter } hist_filter ;
struct TYPE_6__ {scalar_t__ report_hierarchy; } ;

/* Variables and functions */
 int /*<<< orphan*/  he_stat__add_stat (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  hists__calc_col_len (struct hists*,struct hist_entry*) ; 
 int /*<<< orphan*/  hists__inc_filter_stats (struct hists*,struct hist_entry*) ; 
 TYPE_2__ symbol_conf ; 

__attribute__((used)) static void hists__remove_entry_filter(struct hists *hists, struct hist_entry *h,
				       enum hist_filter filter)
{
	h->filtered &= ~(1 << filter);

	if (symbol_conf.report_hierarchy) {
		struct hist_entry *parent = h->parent_he;

		while (parent) {
			he_stat__add_stat(&parent->stat, &h->stat);

			parent->filtered &= ~(1 << filter);

			if (parent->filtered)
				goto next;

			/* force fold unfiltered entry for simplicity */
			parent->unfolded = false;
			parent->has_no_entry = false;
			parent->row_offset = 0;
			parent->nr_rows = 0;
next:
			parent = parent->parent_he;
		}
	}

	if (h->filtered)
		return;

	/* force fold unfiltered entry for simplicity */
	h->unfolded = false;
	h->has_no_entry = false;
	h->row_offset = 0;
	h->nr_rows = 0;

	hists->stats.nr_non_filtered_samples += h->stat.nr_events;

	hists__inc_filter_stats(hists, h);
	hists__calc_col_len(hists, h);
}