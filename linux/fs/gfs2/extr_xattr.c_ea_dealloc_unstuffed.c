#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {scalar_t__ rd_length; int /*<<< orphan*/  rd_gl; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_ctime; } ;
struct gfs2_inode {TYPE_1__ i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct gfs2_ea_header {unsigned int ea_num_ptrs; int /*<<< orphan*/  ea_type; int /*<<< orphan*/  ea_flags; int /*<<< orphan*/  ea_rec_len; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__* GFS2_EA2DATAPTRS (struct gfs2_ea_header*) ; 
 int /*<<< orphan*/  GFS2_EAFLAG_LAST ; 
 int /*<<< orphan*/  GFS2_EATYPE_UNUSED ; 
 scalar_t__ GFS2_EA_IS_LAST (struct gfs2_ea_header*) ; 
 scalar_t__ GFS2_EA_IS_STUFFED (struct gfs2_ea_header*) ; 
 scalar_t__ GFS2_EA_REC_LEN (struct gfs2_ea_header*) ; 
 struct gfs2_sbd* GFS2_SB (TYPE_1__*) ; 
 int /*<<< orphan*/  I_DIRTY_DATASYNC ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 scalar_t__ RES_DINODE ; 
 scalar_t__ RES_EATTR ; 
 scalar_t__ RES_QUOTA ; 
 scalar_t__ RES_STATFS ; 
 int /*<<< orphan*/  __mark_inode_dirty (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  current_time (TYPE_1__*) ; 
 int /*<<< orphan*/  gfs2_add_inode_blocks (TYPE_1__*,int) ; 
 struct gfs2_rgrpd* gfs2_blk2rgrpd (struct gfs2_sbd*,scalar_t__,int) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_free_meta (struct gfs2_inode*,struct gfs2_rgrpd*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 

__attribute__((used)) static int ea_dealloc_unstuffed(struct gfs2_inode *ip, struct buffer_head *bh,
				struct gfs2_ea_header *ea,
				struct gfs2_ea_header *prev, void *private)
{
	int *leave = private;
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_rgrpd *rgd;
	struct gfs2_holder rg_gh;
	__be64 *dataptrs;
	u64 bn = 0;
	u64 bstart = 0;
	unsigned int blen = 0;
	unsigned int blks = 0;
	unsigned int x;
	int error;

	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	if (GFS2_EA_IS_STUFFED(ea))
		return 0;

	dataptrs = GFS2_EA2DATAPTRS(ea);
	for (x = 0; x < ea->ea_num_ptrs; x++, dataptrs++) {
		if (*dataptrs) {
			blks++;
			bn = be64_to_cpu(*dataptrs);
		}
	}
	if (!blks)
		return 0;

	rgd = gfs2_blk2rgrpd(sdp, bn, 1);
	if (!rgd) {
		gfs2_consist_inode(ip);
		return -EIO;
	}

	error = gfs2_glock_nq_init(rgd->rd_gl, LM_ST_EXCLUSIVE, 0, &rg_gh);
	if (error)
		return error;

	error = gfs2_trans_begin(sdp, rgd->rd_length + RES_DINODE +
				 RES_EATTR + RES_STATFS + RES_QUOTA, blks);
	if (error)
		goto out_gunlock;

	gfs2_trans_add_meta(ip->i_gl, bh);

	dataptrs = GFS2_EA2DATAPTRS(ea);
	for (x = 0; x < ea->ea_num_ptrs; x++, dataptrs++) {
		if (!*dataptrs)
			break;
		bn = be64_to_cpu(*dataptrs);

		if (bstart + blen == bn)
			blen++;
		else {
			if (bstart)
				gfs2_free_meta(ip, rgd, bstart, blen);
			bstart = bn;
			blen = 1;
		}

		*dataptrs = 0;
		gfs2_add_inode_blocks(&ip->i_inode, -1);
	}
	if (bstart)
		gfs2_free_meta(ip, rgd, bstart, blen);

	if (prev && !leave) {
		u32 len;

		len = GFS2_EA_REC_LEN(prev) + GFS2_EA_REC_LEN(ea);
		prev->ea_rec_len = cpu_to_be32(len);

		if (GFS2_EA_IS_LAST(ea))
			prev->ea_flags |= GFS2_EAFLAG_LAST;
	} else {
		ea->ea_type = GFS2_EATYPE_UNUSED;
		ea->ea_num_ptrs = 0;
	}

	ip->i_inode.i_ctime = current_time(&ip->i_inode);
	__mark_inode_dirty(&ip->i_inode, I_DIRTY_DATASYNC);

	gfs2_trans_end(sdp);

out_gunlock:
	gfs2_glock_dq_uninit(&rg_gh);
	return error;
}