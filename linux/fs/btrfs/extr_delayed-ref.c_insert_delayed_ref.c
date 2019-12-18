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
struct btrfs_delayed_ref_node {scalar_t__ action; int ref_mod; int /*<<< orphan*/  add_list; } ;
struct btrfs_delayed_ref_head {int /*<<< orphan*/  lock; int /*<<< orphan*/  ref_add_list; int /*<<< orphan*/  ref_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BTRFS_ADD_DELAYED_REF ; 
 scalar_t__ BTRFS_DROP_DELAYED_REF ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drop_delayed_ref (struct btrfs_trans_handle*,struct btrfs_delayed_ref_root*,struct btrfs_delayed_ref_head*,struct btrfs_delayed_ref_node*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct btrfs_delayed_ref_node* tree_insert (int /*<<< orphan*/ *,struct btrfs_delayed_ref_node*) ; 

__attribute__((used)) static int insert_delayed_ref(struct btrfs_trans_handle *trans,
			      struct btrfs_delayed_ref_root *root,
			      struct btrfs_delayed_ref_head *href,
			      struct btrfs_delayed_ref_node *ref)
{
	struct btrfs_delayed_ref_node *exist;
	int mod;
	int ret = 0;

	spin_lock(&href->lock);
	exist = tree_insert(&href->ref_tree, ref);
	if (!exist)
		goto inserted;

	/* Now we are sure we can merge */
	ret = 1;
	if (exist->action == ref->action) {
		mod = ref->ref_mod;
	} else {
		/* Need to change action */
		if (exist->ref_mod < ref->ref_mod) {
			exist->action = ref->action;
			mod = -exist->ref_mod;
			exist->ref_mod = ref->ref_mod;
			if (ref->action == BTRFS_ADD_DELAYED_REF)
				list_add_tail(&exist->add_list,
					      &href->ref_add_list);
			else if (ref->action == BTRFS_DROP_DELAYED_REF) {
				ASSERT(!list_empty(&exist->add_list));
				list_del(&exist->add_list);
			} else {
				ASSERT(0);
			}
		} else
			mod = -ref->ref_mod;
	}
	exist->ref_mod += mod;

	/* remove existing tail if its ref_mod is zero */
	if (exist->ref_mod == 0)
		drop_delayed_ref(trans, root, href, exist);
	spin_unlock(&href->lock);
	return ret;
inserted:
	if (ref->action == BTRFS_ADD_DELAYED_REF)
		list_add_tail(&ref->add_list, &href->ref_add_list);
	atomic_inc(&root->num_entries);
	spin_unlock(&href->lock);
	return ret;
}