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
struct inode {int i_state; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {scalar_t__ nrpages; struct inode* host; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EIO ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int I_DIRTY_ALL ; 
 int I_DIRTY_PAGES ; 
 int I_DIRTY_SYNC ; 
 int I_DIRTY_TIME ; 
 int file_fdatawait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int file_write_and_wait (struct file*) ; 
 int filemap_fdatawrite_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_ail_flush (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 int sync_inode_metadata (struct inode*,int) ; 

__attribute__((used)) static int gfs2_fsync(struct file *file, loff_t start, loff_t end,
		      int datasync)
{
	struct address_space *mapping = file->f_mapping;
	struct inode *inode = mapping->host;
	int sync_state = inode->i_state & I_DIRTY_ALL;
	struct gfs2_inode *ip = GFS2_I(inode);
	int ret = 0, ret1 = 0;

	if (mapping->nrpages) {
		ret1 = filemap_fdatawrite_range(mapping, start, end);
		if (ret1 == -EIO)
			return ret1;
	}

	if (!gfs2_is_jdata(ip))
		sync_state &= ~I_DIRTY_PAGES;
	if (datasync)
		sync_state &= ~(I_DIRTY_SYNC | I_DIRTY_TIME);

	if (sync_state) {
		ret = sync_inode_metadata(inode, 1);
		if (ret)
			return ret;
		if (gfs2_is_jdata(ip))
			ret = file_write_and_wait(file);
		if (ret)
			return ret;
		gfs2_ail_flush(ip->i_gl, 1);
	}

	if (mapping->nrpages)
		ret = file_fdatawait_range(file, start, end);

	return ret ? ret : ret1;
}