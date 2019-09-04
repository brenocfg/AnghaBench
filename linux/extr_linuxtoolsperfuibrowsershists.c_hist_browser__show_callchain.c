#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  period; } ;
struct hist_entry {int /*<<< orphan*/  sorted_chain; TYPE_2__ stat; TYPE_1__* stat_acc; int /*<<< orphan*/  hists; } ;
struct hist_browser {struct hist_entry* he_selection; } ;
struct callchain_print_arg {scalar_t__ is_current_entry; } ;
typedef  int /*<<< orphan*/  print_callchain_entry_fn ;
typedef  int /*<<< orphan*/  check_output_full_fn ;
struct TYPE_8__ {scalar_t__ mode; } ;
struct TYPE_7__ {scalar_t__ cumulate_callchain; } ;
struct TYPE_5__ {int /*<<< orphan*/  period; } ;

/* Variables and functions */
 scalar_t__ CHAIN_FLAT ; 
 scalar_t__ CHAIN_FOLDED ; 
 TYPE_4__ callchain_param ; 
 int hist_browser__show_callchain_flat (struct hist_browser*,int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct callchain_print_arg*,int /*<<< orphan*/ ) ; 
 int hist_browser__show_callchain_folded (struct hist_browser*,int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct callchain_print_arg*,int /*<<< orphan*/ ) ; 
 int hist_browser__show_callchain_graph (struct hist_browser*,int /*<<< orphan*/ *,int,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct callchain_print_arg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__total_period (int /*<<< orphan*/ ) ; 
 TYPE_3__ symbol_conf ; 

__attribute__((used)) static int hist_browser__show_callchain(struct hist_browser *browser,
					struct hist_entry *entry, int level,
					unsigned short row,
					print_callchain_entry_fn print,
					struct callchain_print_arg *arg,
					check_output_full_fn is_output_full)
{
	u64 total = hists__total_period(entry->hists);
	u64 parent_total;
	int printed;

	if (symbol_conf.cumulate_callchain)
		parent_total = entry->stat_acc->period;
	else
		parent_total = entry->stat.period;

	if (callchain_param.mode == CHAIN_FLAT) {
		printed = hist_browser__show_callchain_flat(browser,
						&entry->sorted_chain, row,
						total, parent_total, print, arg,
						is_output_full);
	} else if (callchain_param.mode == CHAIN_FOLDED) {
		printed = hist_browser__show_callchain_folded(browser,
						&entry->sorted_chain, row,
						total, parent_total, print, arg,
						is_output_full);
	} else {
		printed = hist_browser__show_callchain_graph(browser,
						&entry->sorted_chain, level, row,
						total, parent_total, print, arg,
						is_output_full);
	}

	if (arg->is_current_entry)
		browser->he_selection = entry;

	return printed;
}