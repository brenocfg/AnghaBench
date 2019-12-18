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
struct btrfs_delayed_ref_root {int /*<<< orphan*/  num_heads_ready; int /*<<< orphan*/  num_heads; int /*<<< orphan*/  num_entries; int /*<<< orphan*/  href_root; int /*<<< orphan*/  lock; } ;
struct btrfs_delayed_ref_head {scalar_t__ processing; int /*<<< orphan*/  href_node; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void btrfs_delete_ref_head(struct btrfs_delayed_ref_root *delayed_refs,
			   struct btrfs_delayed_ref_head *head)
{
	lockdep_assert_held(&delayed_refs->lock);
	lockdep_assert_held(&head->lock);

	rb_erase_cached(&head->href_node, &delayed_refs->href_root);
	RB_CLEAR_NODE(&head->href_node);
	atomic_dec(&delayed_refs->num_entries);
	delayed_refs->num_heads--;
	if (head->processing == 0)
		delayed_refs->num_heads_ready--;
}