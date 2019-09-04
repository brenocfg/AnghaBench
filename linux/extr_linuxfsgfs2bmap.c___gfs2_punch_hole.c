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
struct inode {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int dummy; } ;
struct file {int dummy; } ;
typedef  unsigned int loff_t ;
struct TYPE_2__ {scalar_t__ journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  GFS2_JTRUNC_REVOKES ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ RES_DINODE ; 
 int RES_JDATA ; 
 TYPE_1__* current ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_update_time (struct file*) ; 
 int gfs2_block_zero_range (struct inode*,unsigned int,unsigned int) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_journaled_truncate_range (struct inode*,unsigned int,unsigned int) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 unsigned int i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int punch_hole (struct gfs2_inode*,unsigned int,unsigned int) ; 
 int stuffed_zero_range (struct inode*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,unsigned int,unsigned int) ; 

int __gfs2_punch_hole(struct file *file, loff_t offset, loff_t length)
{
	struct inode *inode = file_inode(file);
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	int error;

	if (gfs2_is_jdata(ip))
		error = gfs2_trans_begin(sdp, RES_DINODE + 2 * RES_JDATA,
					 GFS2_JTRUNC_REVOKES);
	else
		error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	if (error)
		return error;

	if (gfs2_is_stuffed(ip)) {
		error = stuffed_zero_range(inode, offset, length);
		if (error)
			goto out;
	} else {
		unsigned int start_off, end_len, blocksize;

		blocksize = i_blocksize(inode);
		start_off = offset & (blocksize - 1);
		end_len = (offset + length) & (blocksize - 1);
		if (start_off) {
			unsigned int len = length;
			if (length > blocksize - start_off)
				len = blocksize - start_off;
			error = gfs2_block_zero_range(inode, offset, len);
			if (error)
				goto out;
			if (start_off + length < blocksize)
				end_len = 0;
		}
		if (end_len) {
			error = gfs2_block_zero_range(inode,
				offset + length - end_len, end_len);
			if (error)
				goto out;
		}
	}

	if (gfs2_is_jdata(ip)) {
		BUG_ON(!current->journal_info);
		gfs2_journaled_truncate_range(inode, offset, length);
	} else
		truncate_pagecache_range(inode, offset, offset + length - 1);

	file_update_time(file);
	mark_inode_dirty(inode);

	if (current->journal_info)
		gfs2_trans_end(sdp);

	if (!gfs2_is_stuffed(ip))
		error = punch_hole(ip, offset, length);

out:
	if (current->journal_info)
		gfs2_trans_end(sdp);
	return error;
}