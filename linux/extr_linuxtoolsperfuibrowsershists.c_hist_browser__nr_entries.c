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
typedef  scalar_t__ u32 ;
struct hist_browser {scalar_t__ nr_callchain_rows; TYPE_1__* hists; scalar_t__ nr_non_filtered_entries; scalar_t__ nr_hierarchy_entries; } ;
struct TYPE_4__ {scalar_t__ report_hierarchy; } ;
struct TYPE_3__ {scalar_t__ nr_entries; } ;

/* Variables and functions */
 scalar_t__ hist_browser__get_folding (struct hist_browser*) ; 
 scalar_t__ hist_browser__has_filter (struct hist_browser*) ; 
 TYPE_2__ symbol_conf ; 

__attribute__((used)) static u32 hist_browser__nr_entries(struct hist_browser *hb)
{
	u32 nr_entries;

	if (symbol_conf.report_hierarchy)
		nr_entries = hb->nr_hierarchy_entries;
	else if (hist_browser__has_filter(hb))
		nr_entries = hb->nr_non_filtered_entries;
	else
		nr_entries = hb->hists->nr_entries;

	hb->nr_callchain_rows = hist_browser__get_folding(hb);
	return nr_entries + hb->nr_callchain_rows;
}