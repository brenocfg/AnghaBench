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
struct rb_root_cached {int dummy; } ;
struct hists {int /*<<< orphan*/  nr_non_filtered_entries; int /*<<< orphan*/  nr_entries; struct rb_root_cached entries; struct rb_root_cached* entries_in; struct rb_root_cached entries_collapsed; } ;
struct hist_entry {int /*<<< orphan*/  filtered; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  rb_node_in; TYPE_1__* parent_he; } ;
struct TYPE_2__ {struct rb_root_cached hroot_out; struct rb_root_cached hroot_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  hist_entry__delete (struct hist_entry*) ; 
 scalar_t__ hists__has (struct hists*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  need_collapse ; 
 int /*<<< orphan*/  rb_erase_cached (int /*<<< orphan*/ *,struct rb_root_cached*) ; 

__attribute__((used)) static void hists__delete_entry(struct hists *hists, struct hist_entry *he)
{
	struct rb_root_cached *root_in;
	struct rb_root_cached *root_out;

	if (he->parent_he) {
		root_in  = &he->parent_he->hroot_in;
		root_out = &he->parent_he->hroot_out;
	} else {
		if (hists__has(hists, need_collapse))
			root_in = &hists->entries_collapsed;
		else
			root_in = hists->entries_in;
		root_out = &hists->entries;
	}

	rb_erase_cached(&he->rb_node_in, root_in);
	rb_erase_cached(&he->rb_node, root_out);

	--hists->nr_entries;
	if (!he->filtered)
		--hists->nr_non_filtered_entries;

	hist_entry__delete(he);
}