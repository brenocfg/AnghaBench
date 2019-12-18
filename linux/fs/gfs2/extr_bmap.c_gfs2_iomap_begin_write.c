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
struct metapath {int dummy; } ;
struct iomap {scalar_t__ type; int length; int /*<<< orphan*/ * page_ops; int /*<<< orphan*/  offset; } ;
struct inode {int i_blkbits; } ;
struct gfs2_trans {scalar_t__ tr_num_buf_new; } ;
struct gfs2_sbd {struct inode* sd_rindex; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_alloc_parms {unsigned int target; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct gfs2_trans* journal_info; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IOMAP_HOLE ; 
 int /*<<< orphan*/  I_DIRTY_DATASYNC ; 
 unsigned int RES_DINODE ; 
 scalar_t__ RES_QUOTA ; 
 int RES_STATFS ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 int gfs2_iomap_alloc (struct inode*,struct iomap*,struct metapath*) ; 
 int gfs2_iomap_get (struct inode*,int /*<<< orphan*/ ,int,unsigned int,struct iomap*,struct metapath*) ; 
 int /*<<< orphan*/  gfs2_iomap_page_ops ; 
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
 int /*<<< orphan*/  punch_hole (struct gfs2_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_metapath (struct metapath*) ; 

__attribute__((used)) static int gfs2_iomap_begin_write(struct inode *inode, loff_t pos,
				  loff_t length, unsigned flags,
				  struct iomap *iomap,
				  struct metapath *mp)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	bool unstuff;
	int ret;

	unstuff = gfs2_is_stuffed(ip) &&
		  pos + length > gfs2_max_stuffed_size(ip);

	if (unstuff || iomap->type == IOMAP_HOLE) {
		unsigned int data_blocks, ind_blocks;
		struct gfs2_alloc_parms ap = {};
		unsigned int rblocks;
		struct gfs2_trans *tr;

		gfs2_write_calc_reserv(ip, iomap->length, &data_blocks,
				       &ind_blocks);
		ap.target = data_blocks + ind_blocks;
		ret = gfs2_quota_lock_check(ip, &ap);
		if (ret)
			return ret;

		ret = gfs2_inplace_reserve(ip, &ap);
		if (ret)
			goto out_qunlock;

		rblocks = RES_DINODE + ind_blocks;
		if (gfs2_is_jdata(ip))
			rblocks += data_blocks;
		if (ind_blocks || data_blocks)
			rblocks += RES_STATFS + RES_QUOTA;
		if (inode == sdp->sd_rindex)
			rblocks += 2 * RES_STATFS;
		rblocks += gfs2_rg_blocks(ip, data_blocks + ind_blocks);

		ret = gfs2_trans_begin(sdp, rblocks,
				       iomap->length >> inode->i_blkbits);
		if (ret)
			goto out_trans_fail;

		if (unstuff) {
			ret = gfs2_unstuff_dinode(ip, NULL);
			if (ret)
				goto out_trans_end;
			release_metapath(mp);
			ret = gfs2_iomap_get(inode, iomap->offset,
					     iomap->length, flags, iomap, mp);
			if (ret)
				goto out_trans_end;
		}

		if (iomap->type == IOMAP_HOLE) {
			ret = gfs2_iomap_alloc(inode, iomap, mp);
			if (ret) {
				gfs2_trans_end(sdp);
				gfs2_inplace_release(ip);
				punch_hole(ip, iomap->offset, iomap->length);
				goto out_qunlock;
			}
		}

		tr = current->journal_info;
		if (tr->tr_num_buf_new)
			__mark_inode_dirty(inode, I_DIRTY_DATASYNC);

		gfs2_trans_end(sdp);
	}

	if (gfs2_is_stuffed(ip) || gfs2_is_jdata(ip))
		iomap->page_ops = &gfs2_iomap_page_ops;
	return 0;

out_trans_end:
	gfs2_trans_end(sdp);
out_trans_fail:
	gfs2_inplace_release(ip);
out_qunlock:
	gfs2_quota_unlock(ip);
	return ret;
}