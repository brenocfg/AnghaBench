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
typedef  unsigned int u64 ;
struct inode {unsigned int i_size; } ;
struct gfs2_sbd {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct gfs2_inode {TYPE_1__ i_inode; int /*<<< orphan*/  i_diskflags; int /*<<< orphan*/  i_gl; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct TYPE_4__ {scalar_t__ journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_DIF_TRUNC_IN_PROG ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  GFS2_JTRUNC_REVOKES ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ RES_DINODE ; 
 scalar_t__ RES_JDATA ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  current_time (TYPE_1__*) ; 
 int gfs2_block_zero_range (struct inode*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gfs2_buffer_clear_tail (struct buffer_head*,unsigned int) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int gfs2_is_jdata (struct gfs2_inode*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 int gfs2_journaled_truncate (struct inode*,unsigned int,unsigned int) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 unsigned int i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,unsigned int) ; 

__attribute__((used)) static int trunc_start(struct inode *inode, u64 newsize)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct buffer_head *dibh = NULL;
	int journaled = gfs2_is_jdata(ip);
	u64 oldsize = inode->i_size;
	int error;

	if (journaled)
		error = gfs2_trans_begin(sdp, RES_DINODE + RES_JDATA, GFS2_JTRUNC_REVOKES);
	else
		error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	if (error)
		return error;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		goto out;

	gfs2_trans_add_meta(ip->i_gl, dibh);

	if (gfs2_is_stuffed(ip)) {
		gfs2_buffer_clear_tail(dibh, sizeof(struct gfs2_dinode) + newsize);
	} else {
		unsigned int blocksize = i_blocksize(inode);
		unsigned int offs = newsize & (blocksize - 1);
		if (offs) {
			error = gfs2_block_zero_range(inode, newsize,
						      blocksize - offs);
			if (error)
				goto out;
		}
		ip->i_diskflags |= GFS2_DIF_TRUNC_IN_PROG;
	}

	i_size_write(inode, newsize);
	ip->i_inode.i_mtime = ip->i_inode.i_ctime = current_time(&ip->i_inode);
	gfs2_dinode_out(ip, dibh->b_data);

	if (journaled)
		error = gfs2_journaled_truncate(inode, oldsize, newsize);
	else
		truncate_pagecache(inode, newsize);

out:
	brelse(dibh);
	if (current->journal_info)
		gfs2_trans_end(sdp);
	return error;
}