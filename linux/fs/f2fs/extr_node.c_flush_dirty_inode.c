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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_P_SB (struct page*) ; 
 int /*<<< orphan*/  f2fs_match_ino ; 
 int /*<<< orphan*/  f2fs_update_inode (struct inode*,struct page*) ; 
 struct inode* find_inode_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ino_of_node (struct page*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static bool flush_dirty_inode(struct page *page)
{
	struct f2fs_sb_info *sbi = F2FS_P_SB(page);
	struct inode *inode;
	nid_t ino = ino_of_node(page);

	inode = find_inode_nowait(sbi->sb, ino, f2fs_match_ino, NULL);
	if (!inode)
		return false;

	f2fs_update_inode(inode, page);
	unlock_page(page);

	iput(inode);
	return true;
}