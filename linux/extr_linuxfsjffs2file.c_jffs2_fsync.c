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
struct jffs2_sb_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 struct jffs2_sb_info* JFFS2_SB_INFO (int /*<<< orphan*/ ) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  jffs2_flush_wbuf_gc (struct jffs2_sb_info*,int /*<<< orphan*/ ) ; 

int jffs2_fsync(struct file *filp, loff_t start, loff_t end, int datasync)
{
	struct inode *inode = filp->f_mapping->host;
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	int ret;

	ret = file_write_and_wait_range(filp, start, end);
	if (ret)
		return ret;

	inode_lock(inode);
	/* Trigger GC to flush any pending writes for this inode */
	jffs2_flush_wbuf_gc(c, inode->i_ino);
	inode_unlock(inode);

	return 0;
}