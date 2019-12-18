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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct TYPE_3__ {scalar_t__ ar_quota; } ;
struct gfs2_sbd {TYPE_1__ sd_args; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; TYPE_2__ i_inode; } ;
struct gfs2_alloc_parms {int target; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 scalar_t__ GFS2_QUOTA_OFF ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ RES_DINODE ; 
 int /*<<< orphan*/  RES_JDATA ; 
 scalar_t__ RES_QUOTA ; 
 scalar_t__ RES_RG_BIT ; 
 scalar_t__ RES_STATFS ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  current_time (TYPE_2__*) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 scalar_t__ gfs2_max_stuffed_size (struct gfs2_inode*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int gfs2_quota_lock_check (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int gfs2_unstuff_dinode (struct gfs2_inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,scalar_t__) ; 

__attribute__((used)) static int do_grow(struct inode *inode, u64 size)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_alloc_parms ap = { .target = 1, };
	struct buffer_head *dibh;
	int error;
	int unstuff = 0;

	if (gfs2_is_stuffed(ip) && size > gfs2_max_stuffed_size(ip)) {
		error = gfs2_quota_lock_check(ip, &ap);
		if (error)
			return error;

		error = gfs2_inplace_reserve(ip, &ap);
		if (error)
			goto do_grow_qunlock;
		unstuff = 1;
	}

	error = gfs2_trans_begin(sdp, RES_DINODE + RES_STATFS + RES_RG_BIT +
				 (unstuff &&
				  gfs2_is_jdata(ip) ? RES_JDATA : 0) +
				 (sdp->sd_args.ar_quota == GFS2_QUOTA_OFF ?
				  0 : RES_QUOTA), 0);
	if (error)
		goto do_grow_release;

	if (unstuff) {
		error = gfs2_unstuff_dinode(ip, NULL);
		if (error)
			goto do_end_trans;
	}

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		goto do_end_trans;

	truncate_setsize(inode, size);
	ip->i_inode.i_mtime = ip->i_inode.i_ctime = current_time(&ip->i_inode);
	gfs2_trans_add_meta(ip->i_gl, dibh);
	gfs2_dinode_out(ip, dibh->b_data);
	brelse(dibh);

do_end_trans:
	gfs2_trans_end(sdp);
do_grow_release:
	if (unstuff) {
		gfs2_inplace_release(ip);
do_grow_qunlock:
		gfs2_quota_unlock(ip);
	}
	return error;
}