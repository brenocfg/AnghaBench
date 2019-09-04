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
struct hist_entry {int unfolded; int has_children; int nr_rows; int /*<<< orphan*/  sorted_chain; scalar_t__ leaf; } ;
struct hist_browser {int dummy; } ;

/* Variables and functions */
 int callchain__set_folding (int /*<<< orphan*/ *,int) ; 
 int hierarchy_set_folding (struct hist_browser*,struct hist_entry*,int) ; 
 int /*<<< orphan*/  hist_entry__init_have_children (struct hist_entry*) ; 

__attribute__((used)) static void __hist_entry__set_folding(struct hist_entry *he,
				      struct hist_browser *hb, bool unfold)
{
	hist_entry__init_have_children(he);
	he->unfolded = unfold ? he->has_children : false;

	if (he->has_children) {
		int n;

		if (he->leaf)
			n = callchain__set_folding(&he->sorted_chain, unfold);
		else
			n = hierarchy_set_folding(hb, he, unfold);

		he->nr_rows = unfold ? n : 0;
	} else
		he->nr_rows = 0;
}