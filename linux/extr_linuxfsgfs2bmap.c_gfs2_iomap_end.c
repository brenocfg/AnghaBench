#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iomap {scalar_t__ type; int flags; struct buffer_head* private; } ;
struct inode {int dummy; } ;
struct gfs2_trans {scalar_t__ tr_num_buf_new; } ;
struct gfs2_sbd {scalar_t__ sd_rindex_uptodate; struct inode* sd_rindex; } ;
struct gfs2_inode {TYPE_1__* i_qadata; int /*<<< orphan*/  i_gl; } ;
struct buffer_head {int dummy; } ;
typedef  int ssize_t ;
typedef  int loff_t ;
struct TYPE_4__ {struct gfs2_trans* journal_info; } ;
struct TYPE_3__ {scalar_t__ qa_qd_num; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 unsigned int IOMAP_DIRECT ; 
 int IOMAP_F_NEW ; 
 scalar_t__ IOMAP_INLINE ; 
 unsigned int IOMAP_WRITE ; 
 int /*<<< orphan*/  I_DIRTY_DATASYNC ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_fs_space (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_ordered_add_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_write_unlock (struct inode*) ; 
 int i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  punch_hole (struct gfs2_inode*,int,int) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,int,int) ; 

__attribute__((used)) static int gfs2_iomap_end(struct inode *inode, loff_t pos, loff_t length,
			  ssize_t written, unsigned flags, struct iomap *iomap)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_trans *tr = current->journal_info;
	struct buffer_head *dibh = iomap->private;

	if ((flags & (IOMAP_WRITE | IOMAP_DIRECT)) != IOMAP_WRITE)
		goto out;

	if (iomap->type != IOMAP_INLINE) {
		gfs2_ordered_add_inode(ip);

		if (tr->tr_num_buf_new)
			__mark_inode_dirty(inode, I_DIRTY_DATASYNC);
		else
			gfs2_trans_add_meta(ip->i_gl, dibh);
	}

	if (inode == sdp->sd_rindex) {
		adjust_fs_space(inode);
		sdp->sd_rindex_uptodate = 0;
	}

	gfs2_trans_end(sdp);
	gfs2_inplace_release(ip);

	if (length != written && (iomap->flags & IOMAP_F_NEW)) {
		/* Deallocate blocks that were just allocated. */
		loff_t blockmask = i_blocksize(inode) - 1;
		loff_t end = (pos + length) & ~blockmask;

		pos = (pos + written + blockmask) & ~blockmask;
		if (pos < end) {
			truncate_pagecache_range(inode, pos, end - 1);
			punch_hole(ip, pos, end - pos);
		}
	}

	if (ip->i_qadata && ip->i_qadata->qa_qd_num)
		gfs2_quota_unlock(ip);
	gfs2_write_unlock(inode);

out:
	if (dibh)
		brelse(dibh);
	return 0;
}