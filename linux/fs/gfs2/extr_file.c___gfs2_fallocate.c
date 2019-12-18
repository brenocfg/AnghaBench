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
struct inode {int i_blkbits; int const i_size; } ;
struct TYPE_3__ {int sb_bsize; int sb_bsize_shift; } ;
struct gfs2_sbd {int sd_max_rg_data; TYPE_1__ sd_sb; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_alloc_parms {unsigned int min_target; unsigned int target; int allowed; int /*<<< orphan*/  aflags; } ;
struct file {int f_flags; TYPE_2__* f_mapping; } ;
typedef  int loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FALLOC_FL_KEEP_SIZE ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IS_SYNC (int /*<<< orphan*/ ) ; 
 int O_DSYNC ; 
 int PAGE_SIZE ; 
 unsigned int RES_DINODE ; 
 unsigned int RES_QUOTA ; 
 unsigned int RES_RG_HDR ; 
 unsigned int RES_STATFS ; 
 int UINT_MAX ; 
 int __O_SYNC ; 
 int /*<<< orphan*/  calc_max_reserv (struct gfs2_inode*,int*,unsigned int*,unsigned int*,int) ; 
 int fallocate_chunk (struct inode*,int,int,int) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_update_time (struct file*) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 int gfs2_quota_lock_check (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 unsigned int gfs2_rg_blocks (struct gfs2_inode*,unsigned int) ; 
 int /*<<< orphan*/  gfs2_size_hint (struct file*,int,int) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,unsigned int,int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_write_alloc_required (struct gfs2_inode*,int,int) ; 
 int /*<<< orphan*/  gfs2_write_calc_reserv (struct gfs2_inode*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int const) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 long vfs_fsync_range (struct file*,int const,int const,int) ; 

__attribute__((used)) static long __gfs2_fallocate(struct file *file, int mode, loff_t offset, loff_t len)
{
	struct inode *inode = file_inode(file);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_alloc_parms ap = { .aflags = 0, };
	unsigned int data_blocks = 0, ind_blocks = 0, rblocks;
	loff_t bytes, max_bytes, max_blks;
	int error;
	const loff_t pos = offset;
	const loff_t count = len;
	loff_t bsize_mask = ~((loff_t)sdp->sd_sb.sb_bsize - 1);
	loff_t next = (offset + len - 1) >> sdp->sd_sb.sb_bsize_shift;
	loff_t max_chunk_size = UINT_MAX & bsize_mask;

	next = (next + 1) << sdp->sd_sb.sb_bsize_shift;

	offset &= bsize_mask;

	len = next - offset;
	bytes = sdp->sd_max_rg_data * sdp->sd_sb.sb_bsize / 2;
	if (!bytes)
		bytes = UINT_MAX;
	bytes &= bsize_mask;
	if (bytes == 0)
		bytes = sdp->sd_sb.sb_bsize;

	gfs2_size_hint(file, offset, len);

	gfs2_write_calc_reserv(ip, PAGE_SIZE, &data_blocks, &ind_blocks);
	ap.min_target = data_blocks + ind_blocks;

	while (len > 0) {
		if (len < bytes)
			bytes = len;
		if (!gfs2_write_alloc_required(ip, offset, bytes)) {
			len -= bytes;
			offset += bytes;
			continue;
		}

		/* We need to determine how many bytes we can actually
		 * fallocate without exceeding quota or going over the
		 * end of the fs. We start off optimistically by assuming
		 * we can write max_bytes */
		max_bytes = (len > max_chunk_size) ? max_chunk_size : len;

		/* Since max_bytes is most likely a theoretical max, we
		 * calculate a more realistic 'bytes' to serve as a good
		 * starting point for the number of bytes we may be able
		 * to write */
		gfs2_write_calc_reserv(ip, bytes, &data_blocks, &ind_blocks);
		ap.target = data_blocks + ind_blocks;

		error = gfs2_quota_lock_check(ip, &ap);
		if (error)
			return error;
		/* ap.allowed tells us how many blocks quota will allow
		 * us to write. Check if this reduces max_blks */
		max_blks = UINT_MAX;
		if (ap.allowed)
			max_blks = ap.allowed;

		error = gfs2_inplace_reserve(ip, &ap);
		if (error)
			goto out_qunlock;

		/* check if the selected rgrp limits our max_blks further */
		if (ap.allowed && ap.allowed < max_blks)
			max_blks = ap.allowed;

		/* Almost done. Calculate bytes that can be written using
		 * max_blks. We also recompute max_bytes, data_blocks and
		 * ind_blocks */
		calc_max_reserv(ip, &max_bytes, &data_blocks,
				&ind_blocks, max_blks);

		rblocks = RES_DINODE + ind_blocks + RES_STATFS + RES_QUOTA +
			  RES_RG_HDR + gfs2_rg_blocks(ip, data_blocks + ind_blocks);
		if (gfs2_is_jdata(ip))
			rblocks += data_blocks ? data_blocks : 1;

		error = gfs2_trans_begin(sdp, rblocks,
					 PAGE_SIZE >> inode->i_blkbits);
		if (error)
			goto out_trans_fail;

		error = fallocate_chunk(inode, offset, max_bytes, mode);
		gfs2_trans_end(sdp);

		if (error)
			goto out_trans_fail;

		len -= max_bytes;
		offset += max_bytes;
		gfs2_inplace_release(ip);
		gfs2_quota_unlock(ip);
	}

	if (!(mode & FALLOC_FL_KEEP_SIZE) && (pos + count) > inode->i_size)
		i_size_write(inode, pos + count);
	file_update_time(file);
	mark_inode_dirty(inode);

	if ((file->f_flags & O_DSYNC) || IS_SYNC(file->f_mapping->host))
		return vfs_fsync_range(file, pos, pos + count - 1,
			       (file->f_flags & __O_SYNC) ? 0 : 1);
	return 0;

out_trans_fail:
	gfs2_inplace_release(ip);
out_qunlock:
	gfs2_quota_unlock(ip);
	return error;
}