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
typedef  int u32 ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mapping; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int i_diskflags; int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct file {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_LINUX_IMMUTABLE ; 
 int EACCES ; 
 int EPERM ; 
 int GFS2_DIF_APPENDONLY ; 
 int GFS2_DIF_IMMUTABLE ; 
 int GFS2_DIF_JDATA ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int GFS2_LFC_SET_FLAGS ; 
 int GFS2_LOG_HEAD_FLUSH_NORMAL ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  RES_DINODE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_fdatawait (int /*<<< orphan*/ ) ; 
 int filemap_fdatawrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int gfs2_gfsflags_to_fsflags (struct inode*,int) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,int /*<<< orphan*/ ,int) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_ordered_del_inode (struct gfs2_inode*) ; 
 int gfs2_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_set_aops (struct inode*) ; 
 int /*<<< orphan*/  gfs2_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  inode_owner_or_capable (struct inode*) ; 
 int /*<<< orphan*/  mnt_drop_write_file (struct file*) ; 
 int mnt_want_write_file (struct file*) ; 
 int vfs_ioc_setflags_prepare (struct inode*,int,int const) ; 

__attribute__((used)) static int do_gfs2_set_flags(struct file *filp, u32 reqflags, u32 mask,
			     const u32 fsflags)
{
	struct inode *inode = file_inode(filp);
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct buffer_head *bh;
	struct gfs2_holder gh;
	int error;
	u32 new_flags, flags, oldflags;

	error = mnt_want_write_file(filp);
	if (error)
		return error;

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
	if (error)
		goto out_drop_write;

	oldflags = gfs2_gfsflags_to_fsflags(inode, ip->i_diskflags);
	error = vfs_ioc_setflags_prepare(inode, oldflags, fsflags);
	if (error)
		goto out;

	error = -EACCES;
	if (!inode_owner_or_capable(inode))
		goto out;

	error = 0;
	flags = ip->i_diskflags;
	new_flags = (flags & ~mask) | (reqflags & mask);
	if ((new_flags ^ flags) == 0)
		goto out;

	error = -EPERM;
	if (IS_IMMUTABLE(inode) && (new_flags & GFS2_DIF_IMMUTABLE))
		goto out;
	if (IS_APPEND(inode) && (new_flags & GFS2_DIF_APPENDONLY))
		goto out;
	if (((new_flags ^ flags) & GFS2_DIF_IMMUTABLE) &&
	    !capable(CAP_LINUX_IMMUTABLE))
		goto out;
	if (!IS_IMMUTABLE(inode)) {
		error = gfs2_permission(inode, MAY_WRITE);
		if (error)
			goto out;
	}
	if ((flags ^ new_flags) & GFS2_DIF_JDATA) {
		if (new_flags & GFS2_DIF_JDATA)
			gfs2_log_flush(sdp, ip->i_gl,
				       GFS2_LOG_HEAD_FLUSH_NORMAL |
				       GFS2_LFC_SET_FLAGS);
		error = filemap_fdatawrite(inode->i_mapping);
		if (error)
			goto out;
		error = filemap_fdatawait(inode->i_mapping);
		if (error)
			goto out;
		if (new_flags & GFS2_DIF_JDATA)
			gfs2_ordered_del_inode(ip);
	}
	error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	if (error)
		goto out;
	error = gfs2_meta_inode_buffer(ip, &bh);
	if (error)
		goto out_trans_end;
	inode->i_ctime = current_time(inode);
	gfs2_trans_add_meta(ip->i_gl, bh);
	ip->i_diskflags = new_flags;
	gfs2_dinode_out(ip, bh->b_data);
	brelse(bh);
	gfs2_set_inode_flags(inode);
	gfs2_set_aops(inode);
out_trans_end:
	gfs2_trans_end(sdp);
out:
	gfs2_glock_dq_uninit(&gh);
out_drop_write:
	mnt_drop_write_file(filp);
	return error;
}