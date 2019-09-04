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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_key {scalar_t__ offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_inode_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_INODE_ITEM_KEY ; 
 int btrfs_insert_empty_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,int) ; 

int btrfs_insert_empty_inode(struct btrfs_trans_handle *trans,
			     struct btrfs_root *root,
			     struct btrfs_path *path, u64 objectid)
{
	struct btrfs_key key;
	int ret;
	key.objectid = objectid;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_insert_empty_item(trans, root, path, &key,
				      sizeof(struct btrfs_inode_item));
	return ret;
}