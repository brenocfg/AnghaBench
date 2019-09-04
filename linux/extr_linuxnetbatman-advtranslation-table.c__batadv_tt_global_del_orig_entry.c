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
struct batadv_tt_orig_list_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  orig_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  vid; } ;
struct batadv_tt_global_entry {int /*<<< orphan*/  orig_list_count; TYPE_1__ common; int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_tt_global_size_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tt_orig_list_entry_put (struct batadv_tt_orig_list_entry*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_batadv_tt_global_del_orig_entry(struct batadv_tt_global_entry *tt_global_entry,
				 struct batadv_tt_orig_list_entry *orig_entry)
{
	lockdep_assert_held(&tt_global_entry->list_lock);

	batadv_tt_global_size_dec(orig_entry->orig_node,
				  tt_global_entry->common.vid);
	atomic_dec(&tt_global_entry->orig_list_count);
	/* requires holding tt_global_entry->list_lock and orig_entry->list
	 * being part of a list
	 */
	hlist_del_rcu(&orig_entry->list);
	batadv_tt_orig_list_entry_put(orig_entry);
}