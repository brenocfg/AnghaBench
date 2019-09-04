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
typedef  int /*<<< orphan*/  u32 ;
struct btrfs_root {scalar_t__ objectid; int /*<<< orphan*/  fs_info; } ;
struct btrfs_inode {struct btrfs_root* root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_LAST_FREE_OBJECTID ; 
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_warn_rl (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void btrfs_print_data_csum_error(struct btrfs_inode *inode,
		u64 logical_start, u32 csum, u32 csum_expected, int mirror_num)
{
	struct btrfs_root *root = inode->root;

	/* Output minus objectid, which is more meaningful */
	if (root->objectid >= BTRFS_LAST_FREE_OBJECTID)
		btrfs_warn_rl(root->fs_info,
	"csum failed root %lld ino %lld off %llu csum 0x%08x expected csum 0x%08x mirror %d",
			root->objectid, btrfs_ino(inode),
			logical_start, csum, csum_expected, mirror_num);
	else
		btrfs_warn_rl(root->fs_info,
	"csum failed root %llu ino %llu off %llu csum 0x%08x expected csum 0x%08x mirror %d",
			root->objectid, btrfs_ino(inode),
			logical_start, csum, csum_expected, mirror_num);
}