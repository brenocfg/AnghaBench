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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct f2fs_sb_info {int /*<<< orphan*/  s_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_CACHE ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_NO_EXTENT ; 
 int S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool f2fs_may_extent_tree(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);

	if (!test_opt(sbi, EXTENT_CACHE) ||
			is_inode_flag_set(inode, FI_NO_EXTENT))
		return false;

	/*
	 * for recovered files during mount do not create extents
	 * if shrinker is not registered.
	 */
	if (list_empty(&sbi->s_list))
		return false;

	return S_ISREG(inode->i_mode);
}