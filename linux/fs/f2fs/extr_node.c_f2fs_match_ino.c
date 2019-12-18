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
struct inode {unsigned long i_ino; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * inode_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  gdirty_list; } ;

/* Variables and functions */
 size_t DIRTY_META ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_DIRTY_INODE ; 
 struct inode* igrab (struct inode*) ; 
 int /*<<< orphan*/  is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int f2fs_match_ino(struct inode *inode, unsigned long ino, void *data)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	bool clean;

	if (inode->i_ino != ino)
		return 0;

	if (!is_inode_flag_set(inode, FI_DIRTY_INODE))
		return 0;

	spin_lock(&sbi->inode_lock[DIRTY_META]);
	clean = list_empty(&F2FS_I(inode)->gdirty_list);
	spin_unlock(&sbi->inode_lock[DIRTY_META]);

	if (clean)
		return 0;

	inode = igrab(inode);
	if (!inode)
		return 0;
	return 1;
}