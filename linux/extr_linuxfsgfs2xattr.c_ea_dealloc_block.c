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
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {int /*<<< orphan*/  rd_gl; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_inode; int /*<<< orphan*/  i_eattr; } ;
struct gfs2_holder {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int EIO ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 scalar_t__ RES_DINODE ; 
 scalar_t__ RES_QUOTA ; 
 scalar_t__ RES_RG_BIT ; 
 scalar_t__ RES_STATFS ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_add_inode_blocks (int /*<<< orphan*/ *,int) ; 
 struct gfs2_rgrpd* gfs2_blk2rgrpd (struct gfs2_sbd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_free_meta (struct gfs2_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 

__attribute__((used)) static int ea_dealloc_block(struct gfs2_inode *ip)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_rgrpd *rgd;
	struct buffer_head *dibh;
	struct gfs2_holder gh;
	int error;

	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	rgd = gfs2_blk2rgrpd(sdp, ip->i_eattr, 1);
	if (!rgd) {
		gfs2_consist_inode(ip);
		return -EIO;
	}

	error = gfs2_glock_nq_init(rgd->rd_gl, LM_ST_EXCLUSIVE, 0, &gh);
	if (error)
		return error;

	error = gfs2_trans_begin(sdp, RES_RG_BIT + RES_DINODE + RES_STATFS +
				 RES_QUOTA, 1);
	if (error)
		goto out_gunlock;

	gfs2_free_meta(ip, ip->i_eattr, 1);

	ip->i_eattr = 0;
	gfs2_add_inode_blocks(&ip->i_inode, -1);

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (!error) {
		gfs2_trans_add_meta(ip->i_gl, dibh);
		gfs2_dinode_out(ip, dibh->b_data);
		brelse(dibh);
	}

	gfs2_trans_end(sdp);

out_gunlock:
	gfs2_glock_dq_uninit(&gh);
	return error;
}