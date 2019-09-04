#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gfs2_sbd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct gfs2_inode {int /*<<< orphan*/  i_rw_mutex; int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_diskflags; TYPE_1__ i_inode; int /*<<< orphan*/  i_no_addr; int /*<<< orphan*/  i_goal; scalar_t__ i_height; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_DIF_TRUNC_IN_PROG ; 
 struct gfs2_sbd* GFS2_SB (TYPE_1__*) ; 
 int /*<<< orphan*/  RES_DINODE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  current_time (TYPE_1__*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_buffer_clear_tail (struct buffer_head*,int) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_ordered_del_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  i_size_read (TYPE_1__*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int trunc_end(struct gfs2_inode *ip)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct buffer_head *dibh;
	int error;

	error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	if (error)
		return error;

	down_write(&ip->i_rw_mutex);

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		goto out;

	if (!i_size_read(&ip->i_inode)) {
		ip->i_height = 0;
		ip->i_goal = ip->i_no_addr;
		gfs2_buffer_clear_tail(dibh, sizeof(struct gfs2_dinode));
		gfs2_ordered_del_inode(ip);
	}
	ip->i_inode.i_mtime = ip->i_inode.i_ctime = current_time(&ip->i_inode);
	ip->i_diskflags &= ~GFS2_DIF_TRUNC_IN_PROG;

	gfs2_trans_add_meta(ip->i_gl, dibh);
	gfs2_dinode_out(ip, dibh->b_data);
	brelse(dibh);

out:
	up_write(&ip->i_rw_mutex);
	gfs2_trans_end(sdp);
	return error;
}