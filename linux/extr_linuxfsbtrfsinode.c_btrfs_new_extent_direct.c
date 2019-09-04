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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_map {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  objectid; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sectorsize; } ;
struct TYPE_2__ {struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_ORDERED_REGULAR ; 
 struct extent_map* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct extent_map*) ; 
 struct extent_map* btrfs_create_dio_extent (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_dec_block_group_reservations (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_free_reserved_extent (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int btrfs_reserve_extent (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_key*,int,int) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_extent_allocation_hint (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct extent_map *btrfs_new_extent_direct(struct inode *inode,
						  u64 start, u64 len)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct extent_map *em;
	struct btrfs_key ins;
	u64 alloc_hint;
	int ret;

	alloc_hint = get_extent_allocation_hint(inode, start, len);
	ret = btrfs_reserve_extent(root, len, len, fs_info->sectorsize,
				   0, alloc_hint, &ins, 1, 1);
	if (ret)
		return ERR_PTR(ret);

	em = btrfs_create_dio_extent(inode, start, ins.offset, start,
				     ins.objectid, ins.offset, ins.offset,
				     ins.offset, BTRFS_ORDERED_REGULAR);
	btrfs_dec_block_group_reservations(fs_info, ins.objectid);
	if (IS_ERR(em))
		btrfs_free_reserved_extent(fs_info, ins.objectid,
					   ins.offset, 1);

	return em;
}