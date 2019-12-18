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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct page* f2fs_get_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_stop_checkpoint (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_update_inode (struct inode*,struct page*) ; 

void f2fs_update_inode_page(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct page *node_page;
retry:
	node_page = f2fs_get_node_page(sbi, inode->i_ino);
	if (IS_ERR(node_page)) {
		int err = PTR_ERR(node_page);
		if (err == -ENOMEM) {
			cond_resched();
			goto retry;
		} else if (err != -ENOENT) {
			f2fs_stop_checkpoint(sbi, false);
		}
		return;
	}
	f2fs_update_inode(inode, node_page);
	f2fs_put_page(node_page, 1);
}