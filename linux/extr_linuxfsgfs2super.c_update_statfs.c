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
struct gfs2_statfs_change_host {scalar_t__ sc_dinodes; scalar_t__ sc_free; scalar_t__ sc_total; } ;
struct gfs2_statfs_change {int dummy; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_statfs_spin; struct gfs2_statfs_change_host sd_statfs_local; struct gfs2_statfs_change_host sd_statfs_master; int /*<<< orphan*/  sd_sc_inode; int /*<<< orphan*/  sd_statfs_inode; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {struct gfs2_statfs_change_host* b_data; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_statfs_change_out (struct gfs2_statfs_change_host*,struct gfs2_statfs_change_host*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  memset (struct gfs2_statfs_change_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void update_statfs(struct gfs2_sbd *sdp, struct buffer_head *m_bh,
		   struct buffer_head *l_bh)
{
	struct gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	struct gfs2_inode *l_ip = GFS2_I(sdp->sd_sc_inode);
	struct gfs2_statfs_change_host *m_sc = &sdp->sd_statfs_master;
	struct gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;

	gfs2_trans_add_meta(l_ip->i_gl, l_bh);
	gfs2_trans_add_meta(m_ip->i_gl, m_bh);

	spin_lock(&sdp->sd_statfs_spin);
	m_sc->sc_total += l_sc->sc_total;
	m_sc->sc_free += l_sc->sc_free;
	m_sc->sc_dinodes += l_sc->sc_dinodes;
	memset(l_sc, 0, sizeof(struct gfs2_statfs_change));
	memset(l_bh->b_data + sizeof(struct gfs2_dinode),
	       0, sizeof(struct gfs2_statfs_change));
	gfs2_statfs_change_out(m_sc, m_bh->b_data + sizeof(struct gfs2_dinode));
	spin_unlock(&sdp->sd_statfs_spin);
}