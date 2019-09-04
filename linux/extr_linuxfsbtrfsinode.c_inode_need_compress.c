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
struct btrfs_fs_info {int dummy; } ;
struct TYPE_2__ {int flags; scalar_t__ prop_compress; scalar_t__ defrag_compress; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_COMPRESS ; 
 int BTRFS_INODE_NOCOMPRESS ; 
 int /*<<< orphan*/  COMPRESS ; 
 int /*<<< orphan*/  FORCE_COMPRESS ; 
 int btrfs_compress_heuristic (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int inode_need_compress(struct inode *inode, u64 start, u64 end)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);

	/* force compress */
	if (btrfs_test_opt(fs_info, FORCE_COMPRESS))
		return 1;
	/* defrag ioctl */
	if (BTRFS_I(inode)->defrag_compress)
		return 1;
	/* bad compression ratios */
	if (BTRFS_I(inode)->flags & BTRFS_INODE_NOCOMPRESS)
		return 0;
	if (btrfs_test_opt(fs_info, COMPRESS) ||
	    BTRFS_I(inode)->flags & BTRFS_INODE_COMPRESS ||
	    BTRFS_I(inode)->prop_compress)
		return btrfs_compress_heuristic(inode, start, end);
	return 0;
}