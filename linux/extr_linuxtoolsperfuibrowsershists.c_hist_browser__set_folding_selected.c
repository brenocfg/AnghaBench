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
struct hist_browser {TYPE_1__ b; int /*<<< orphan*/  he_selection; } ;

/* Variables and functions */
 int /*<<< orphan*/  hist_browser__nr_entries (struct hist_browser*) ; 
 int /*<<< orphan*/  hist_entry__set_folding (int /*<<< orphan*/ ,struct hist_browser*,int) ; 

__attribute__((used)) static void hist_browser__set_folding_selected(struct hist_browser *browser, bool unfold)
{
	if (!browser->he_selection)
		return;

	hist_entry__set_folding(browser->he_selection, browser, unfold);
	browser->b.nr_entries = hist_browser__nr_entries(browser);
}