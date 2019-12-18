#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hist_entry {int /*<<< orphan*/  hists; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIST_FILTER__DSO ; 
 int /*<<< orphan*/  HIST_FILTER__SYMBOL ; 
 int /*<<< orphan*/  HIST_FILTER__THREAD ; 
 int /*<<< orphan*/  check_thread_entry ; 
 int /*<<< orphan*/  hist_entry__check_and_remove_filter (struct hist_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__apply_filters (int /*<<< orphan*/ ,struct hist_entry*) ; 
 int /*<<< orphan*/  perf_hpp__is_dso_entry ; 
 int /*<<< orphan*/  perf_hpp__is_sym_entry ; 

__attribute__((used)) static void hist_entry__apply_hierarchy_filters(struct hist_entry *he)
{
	hist_entry__check_and_remove_filter(he, HIST_FILTER__THREAD,
					    check_thread_entry);

	hist_entry__check_and_remove_filter(he, HIST_FILTER__DSO,
					    perf_hpp__is_dso_entry);

	hist_entry__check_and_remove_filter(he, HIST_FILTER__SYMBOL,
					    perf_hpp__is_sym_entry);

	hists__apply_filters(he->hists, he);
}