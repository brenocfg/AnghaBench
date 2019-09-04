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
struct metapath {int dummy; } ;
struct iomap {scalar_t__ type; int length; scalar_t__ offset; int /*<<< orphan*/  page_done; } ;
struct inode {int i_blkbits; } ;
struct gfs2_sbd {struct inode* sd_rindex; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_alloc_parms {unsigned int target; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IOMAP_HOLE ; 
 unsigned int RES_DINODE ; 
 scalar_t__ RES_QUOTA ; 
 int RES_STATFS ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 int gfs2_iomap_alloc (struct inode*,struct iomap*,unsigned int,struct metapath*) ; 
 int gfs2_iomap_get (struct inode*,scalar_t__,scalar_t__,unsigned int,struct iomap*,struct metapath*) ; 
 int /*<<< orphan*/  gfs2_iomap_journaled_page_done ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 scalar_t__ gfs2_max_stuffed_size (struct gfs2_inode*) ; 
 int gfs2_quota_lock_check (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 scalar_t__ gfs2_rg_blocks (struct gfs2_inode*,unsigned int) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,unsigned int,int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int gfs2_unstuff_dinode (struct gfs2_inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_write_calc_reserv (struct gfs2_inode*,int,unsigned int*,unsigned int*) ; 
 int gfs2_write_lock (struct inode*) ; 
 int /*<<< orphan*/  gfs2_write_unlock (struct inode*) ; 
 int /*<<< orphan*/  punch_hole (struct gfs2_inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  release_metapath (struct metapath*) ; 

__attribute__((used)) static int gfs2_iomap_begin_write(struct inode *inode, loff_t pos,
				  loff_t length, unsigned flags,
				  struct iomap *iomap,
				  struct metapath *mp)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	unsigned int data_blocks = 0, ind_blocks = 0, rblocks;
	bool unstuff, alloc_required;
	int ret;

	ret = gfs2_write_lock(inode);
	if (ret)
		return ret;

	unstuff = gfs2_is_stuffed(ip) &&
		  pos + length > gfs2_max_stuffed_size(ip);

	ret = gfs2_iomap_get(inode, pos, length, flags, iomap, mp);
	if (ret)
		goto out_unlock;

	alloc_required = unstuff || iomap->type == IOMAP_HOLE;

	if (alloc_required || gfs2_is_jdata(ip))
		gfs2_write_calc_reserv(ip, iomap->length, &data_blocks,
				       &ind_blocks);

	if (alloc_required) {
		struct gfs2_alloc_parms ap = {
			.target = data_blocks + ind_blocks
		};

		ret = gfs2_quota_lock_check(ip, &ap);
		if (ret)
			goto out_unlock;

		ret = gfs2_inplace_reserve(ip, &ap);
		if (ret)
			goto out_qunlock;
	}

	rblocks = RES_DINODE + ind_blocks;
	if (gfs2_is_jdata(ip))
		rblocks += data_blocks;
	if (ind_blocks || data_blocks)
		rblocks += RES_STATFS + RES_QUOTA;
	if (inode == sdp->sd_rindex)
		rblocks += 2 * RES_STATFS;
	if (alloc_required)
		rblocks += gfs2_rg_blocks(ip, data_blocks + ind_blocks);

	ret = gfs2_trans_begin(sdp, rblocks, iomap->length >> inode->i_blkbits);
	if (ret)
		goto out_trans_fail;

	if (unstuff) {
		ret = gfs2_unstuff_dinode(ip, NULL);
		if (ret)
			goto out_trans_end;
		release_metapath(mp);
		ret = gfs2_iomap_get(inode, iomap->offset, iomap->length,
				     flags, iomap, mp);
		if (ret)
			goto out_trans_end;
	}

	if (iomap->type == IOMAP_HOLE) {
		ret = gfs2_iomap_alloc(inode, iomap, flags, mp);
		if (ret) {
			gfs2_trans_end(sdp);
			gfs2_inplace_release(ip);
			punch_hole(ip, iomap->offset, iomap->length);
			goto out_qunlock;
		}
	}
	if (!gfs2_is_stuffed(ip) && gfs2_is_jdata(ip))
		iomap->page_done = gfs2_iomap_journaled_page_done;
	return 0;

out_trans_end:
	gfs2_trans_end(sdp);
out_trans_fail:
	if (alloc_required)
		gfs2_inplace_release(ip);
out_qunlock:
	if (alloc_required)
		gfs2_quota_unlock(ip);
out_unlock:
	gfs2_write_unlock(inode);
	return ret;
}