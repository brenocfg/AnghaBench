#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hists {int /*<<< orphan*/  thread_filter; } ;
struct TYPE_2__ {scalar_t__ report_hierarchy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIST_FILTER__THREAD ; 
 int /*<<< orphan*/  hists__filter_by_type (struct hists*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__filter_entry_by_thread ; 
 int /*<<< orphan*/  hists__filter_hierarchy (struct hists*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ symbol_conf ; 

void hists__filter_by_thread(struct hists *hists)
{
	if (symbol_conf.report_hierarchy)
		hists__filter_hierarchy(hists, HIST_FILTER__THREAD,
					hists->thread_filter);
	else
		hists__filter_by_type(hists, HIST_FILTER__THREAD,
				      hists__filter_entry_by_thread);
}