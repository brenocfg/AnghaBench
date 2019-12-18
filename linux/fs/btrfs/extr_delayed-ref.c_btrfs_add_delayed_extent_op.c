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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {TYPE_1__* transaction; } ;
struct btrfs_delayed_ref_root {int /*<<< orphan*/  lock; } ;
struct btrfs_delayed_ref_head {struct btrfs_delayed_extent_op* extent_op; } ;
struct btrfs_delayed_extent_op {int /*<<< orphan*/  is_data; } ;
struct TYPE_2__ {struct btrfs_delayed_ref_root delayed_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_UPDATE_DELAYED_HEAD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  add_delayed_ref_head (struct btrfs_trans_handle*,struct btrfs_delayed_ref_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_delayed_ref_head_cachep ; 
 int /*<<< orphan*/  btrfs_update_delayed_refs_rsv (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  init_delayed_ref_head (struct btrfs_delayed_ref_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct btrfs_delayed_ref_head* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_add_delayed_extent_op(struct btrfs_trans_handle *trans,
				u64 bytenr, u64 num_bytes,
				struct btrfs_delayed_extent_op *extent_op)
{
	struct btrfs_delayed_ref_head *head_ref;
	struct btrfs_delayed_ref_root *delayed_refs;

	head_ref = kmem_cache_alloc(btrfs_delayed_ref_head_cachep, GFP_NOFS);
	if (!head_ref)
		return -ENOMEM;

	init_delayed_ref_head(head_ref, NULL, bytenr, num_bytes, 0, 0,
			      BTRFS_UPDATE_DELAYED_HEAD, extent_op->is_data,
			      false);
	head_ref->extent_op = extent_op;

	delayed_refs = &trans->transaction->delayed_refs;
	spin_lock(&delayed_refs->lock);

	add_delayed_ref_head(trans, head_ref, NULL, BTRFS_UPDATE_DELAYED_HEAD,
			     NULL, NULL, NULL);

	spin_unlock(&delayed_refs->lock);

	/*
	 * Need to update the delayed_refs_rsv with any changes we may have
	 * made.
	 */
	btrfs_update_delayed_refs_rsv(trans);
	return 0;
}