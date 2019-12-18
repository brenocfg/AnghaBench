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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_delayed_ref_root {int /*<<< orphan*/  num_entries; } ;
struct btrfs_delayed_ref_node {scalar_t__ in_tree; int /*<<< orphan*/  add_list; int /*<<< orphan*/  ref_node; } ;
struct btrfs_delayed_ref_head {int /*<<< orphan*/  ref_tree; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_put_delayed_ref (struct btrfs_delayed_ref_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void drop_delayed_ref(struct btrfs_trans_handle *trans,
				    struct btrfs_delayed_ref_root *delayed_refs,
				    struct btrfs_delayed_ref_head *head,
				    struct btrfs_delayed_ref_node *ref)
{
	lockdep_assert_held(&head->lock);
	rb_erase_cached(&ref->ref_node, &head->ref_tree);
	RB_CLEAR_NODE(&ref->ref_node);
	if (!list_empty(&ref->add_list))
		list_del(&ref->add_list);
	ref->in_tree = 0;
	btrfs_put_delayed_ref(ref);
	atomic_dec(&delayed_refs->num_entries);
}