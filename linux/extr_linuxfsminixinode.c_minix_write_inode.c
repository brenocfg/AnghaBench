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
struct writeback_control {scalar_t__ sync_mode; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ INODE_VERSION (struct inode*) ; 
 scalar_t__ MINIX_V1 ; 
 struct buffer_head* V1_minix_update_inode (struct inode*) ; 
 struct buffer_head* V2_minix_update_inode (struct inode*) ; 
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_req (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 

__attribute__((used)) static int minix_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	int err = 0;
	struct buffer_head *bh;

	if (INODE_VERSION(inode) == MINIX_V1)
		bh = V1_minix_update_inode(inode);
	else
		bh = V2_minix_update_inode(inode);
	if (!bh)
		return -EIO;
	if (wbc->sync_mode == WB_SYNC_ALL && buffer_dirty(bh)) {
		sync_dirty_buffer(bh);
		if (buffer_req(bh) && !buffer_uptodate(bh)) {
			printk("IO error syncing minix inode [%s:%08lx]\n",
				inode->i_sb->s_id, inode->i_ino);
			err = -EIO;
		}
	}
	brelse (bh);
	return err;
}