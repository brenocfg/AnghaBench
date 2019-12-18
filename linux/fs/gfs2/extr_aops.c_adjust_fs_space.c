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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct gfs2_statfs_change_host {scalar_t__ sc_total; } ;
struct gfs2_sbd {scalar_t__ sd_rindex_uptodate; int /*<<< orphan*/  sd_statfs_spin; struct gfs2_statfs_change_host sd_statfs_local; struct gfs2_statfs_change_host sd_statfs_master; int /*<<< orphan*/  sd_sc_inode; int /*<<< orphan*/  sd_statfs_inode; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int RES_STATFS ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*,unsigned long long) ; 
 scalar_t__ gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 scalar_t__ gfs2_ri_total (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_statfs_change (struct gfs2_sbd*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_statfs_change_in (struct gfs2_statfs_change_host*,scalar_t__) ; 
 scalar_t__ gfs2_trans_begin (struct gfs2_sbd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_statfs (struct gfs2_sbd*,struct buffer_head*,struct buffer_head*) ; 

void adjust_fs_space(struct inode *inode)
{
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	struct gfs2_inode *l_ip = GFS2_I(sdp->sd_sc_inode);
	struct gfs2_statfs_change_host *m_sc = &sdp->sd_statfs_master;
	struct gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;
	struct buffer_head *m_bh, *l_bh;
	u64 fs_total, new_free;

	if (gfs2_trans_begin(sdp, 2 * RES_STATFS, 0) != 0)
		return;

	/* Total up the file system space, according to the latest rindex. */
	fs_total = gfs2_ri_total(sdp);
	if (gfs2_meta_inode_buffer(m_ip, &m_bh) != 0)
		goto out;

	spin_lock(&sdp->sd_statfs_spin);
	gfs2_statfs_change_in(m_sc, m_bh->b_data +
			      sizeof(struct gfs2_dinode));
	if (fs_total > (m_sc->sc_total + l_sc->sc_total))
		new_free = fs_total - (m_sc->sc_total + l_sc->sc_total);
	else
		new_free = 0;
	spin_unlock(&sdp->sd_statfs_spin);
	fs_warn(sdp, "File system extended by %llu blocks.\n",
		(unsigned long long)new_free);
	gfs2_statfs_change(sdp, new_free, new_free, 0);

	if (gfs2_meta_inode_buffer(l_ip, &l_bh) != 0)
		goto out2;
	update_statfs(sdp, m_bh, l_bh);
	brelse(l_bh);
out2:
	brelse(m_bh);
out:
	sdp->sd_rindex_uptodate = 0;
	gfs2_trans_end(sdp);
}