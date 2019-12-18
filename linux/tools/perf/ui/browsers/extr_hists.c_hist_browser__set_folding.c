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
struct TYPE_2__ {int /*<<< orphan*/  nr_entries; } ;
struct hist_browser {TYPE_1__ b; scalar_t__ nr_callchain_rows; scalar_t__ nr_hierarchy_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hist_browser__set_folding (struct hist_browser*,int) ; 
 int /*<<< orphan*/  hist_browser__nr_entries (struct hist_browser*) ; 
 int /*<<< orphan*/  ui_browser__reset_index (TYPE_1__*) ; 

__attribute__((used)) static void hist_browser__set_folding(struct hist_browser *browser, bool unfold)
{
	browser->nr_hierarchy_entries = 0;
	browser->nr_callchain_rows = 0;
	__hist_browser__set_folding(browser, unfold);

	browser->b.nr_entries = hist_browser__nr_entries(browser);
	/* Go to the start, we may be way after valid entries after a collapse */
	ui_browser__reset_index(&browser->b);
}