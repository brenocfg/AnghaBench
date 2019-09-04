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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_uuid_tree_remove (struct btrfs_trans_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfs_uuid_iter_rem(struct btrfs_root *uuid_root, u8 *uuid, u8 type,
			       u64 subid)
{
	struct btrfs_trans_handle *trans;
	int ret;

	/* 1 - for the uuid item */
	trans = btrfs_start_transaction(uuid_root, 1);
	if (IS_ERR(trans)) {
		ret = PTR_ERR(trans);
		goto out;
	}

	ret = btrfs_uuid_tree_remove(trans, uuid, type, subid);
	btrfs_end_transaction(trans);

out:
	return ret;
}