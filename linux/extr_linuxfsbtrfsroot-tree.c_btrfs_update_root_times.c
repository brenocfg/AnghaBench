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
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct btrfs_root_item {int /*<<< orphan*/  ctime; } ;
struct btrfs_root {int /*<<< orphan*/  root_item_lock; struct btrfs_root_item root_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_set_root_ctransid (struct btrfs_root_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_timespec_nsec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_timespec_sec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_update_root_times(struct btrfs_trans_handle *trans,
			     struct btrfs_root *root)
{
	struct btrfs_root_item *item = &root->root_item;
	struct timespec64 ct;

	ktime_get_real_ts64(&ct);
	spin_lock(&root->root_item_lock);
	btrfs_set_root_ctransid(item, trans->transid);
	btrfs_set_stack_timespec_sec(&item->ctime, ct.tv_sec);
	btrfs_set_stack_timespec_nsec(&item->ctime, ct.tv_nsec);
	spin_unlock(&root->root_item_lock);
}