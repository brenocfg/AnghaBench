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
struct iomap {int flags; int /*<<< orphan*/  type; } ;
struct inode {int dummy; } ;
struct gfs2_sbd {struct inode* sd_rindex; } ;
struct gfs2_inode {TYPE_2__* i_gl; TYPE_1__* i_qadata; } ;
typedef  int ssize_t ;
typedef  int loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  gl_flags; } ;
struct TYPE_3__ {scalar_t__ qa_qd_num; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  GLF_DIRTY ; 
 unsigned int IOMAP_DIRECT ; 
 int IOMAP_F_NEW ; 
 int IOMAP_F_SIZE_CHANGED ; 
 int /*<<< orphan*/  IOMAP_HOLE ; 
#define  IOMAP_WRITE 129 
#define  IOMAP_ZERO 128 
 int /*<<< orphan*/  adjust_fs_space (struct inode*) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 scalar_t__ gfs2_iomap_need_write_lock (unsigned int) ; 
 int /*<<< orphan*/  gfs2_is_stuffed (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_ordered_add_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_write_unlock (struct inode*) ; 
 int i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  punch_hole (struct gfs2_inode*,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gfs2_iomap_end(struct inode *inode, loff_t pos, loff_t length,
			  ssize_t written, unsigned flags, struct iomap *iomap)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);

	switch (flags & (IOMAP_WRITE | IOMAP_ZERO)) {
	case IOMAP_WRITE:
		if (flags & IOMAP_DIRECT)
			return 0;
		break;
	case IOMAP_ZERO:
		 if (iomap->type == IOMAP_HOLE)
			 return 0;
		 break;
	default:
		 return 0;
	}

	if (!gfs2_is_stuffed(ip))
		gfs2_ordered_add_inode(ip);

	if (inode == sdp->sd_rindex)
		adjust_fs_space(inode);

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

	if (unlikely(!written))
		goto out_unlock;

	if (iomap->flags & IOMAP_F_SIZE_CHANGED)
		mark_inode_dirty(inode);
	set_bit(GLF_DIRTY, &ip->i_gl->gl_flags);

out_unlock:
	if (gfs2_iomap_need_write_lock(flags))
		gfs2_write_unlock(inode);
	return 0;
}