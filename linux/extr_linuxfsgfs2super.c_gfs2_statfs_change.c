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
struct gfs2_statfs_change_host {int sc_free; int /*<<< orphan*/  sc_dinodes; int /*<<< orphan*/  sc_total; } ;
struct TYPE_2__ {int ar_statfs_percent; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_statfs_spin; TYPE_1__ sd_args; struct gfs2_statfs_change_host sd_statfs_master; struct gfs2_statfs_change_host sd_statfs_local; int /*<<< orphan*/  sd_sc_inode; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int s64 ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_statfs_change_out (struct gfs2_statfs_change_host*,scalar_t__) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_wake_up_statfs (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void gfs2_statfs_change(struct gfs2_sbd *sdp, s64 total, s64 free,
			s64 dinodes)
{
	struct gfs2_inode *l_ip = GFS2_I(sdp->sd_sc_inode);
	struct gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;
	struct gfs2_statfs_change_host *m_sc = &sdp->sd_statfs_master;
	struct buffer_head *l_bh;
	s64 x, y;
	int need_sync = 0;
	int error;

	error = gfs2_meta_inode_buffer(l_ip, &l_bh);
	if (error)
		return;

	gfs2_trans_add_meta(l_ip->i_gl, l_bh);

	spin_lock(&sdp->sd_statfs_spin);
	l_sc->sc_total += total;
	l_sc->sc_free += free;
	l_sc->sc_dinodes += dinodes;
	gfs2_statfs_change_out(l_sc, l_bh->b_data + sizeof(struct gfs2_dinode));
	if (sdp->sd_args.ar_statfs_percent) {
		x = 100 * l_sc->sc_free;
		y = m_sc->sc_free * sdp->sd_args.ar_statfs_percent;
		if (x >= y || x <= -y)
			need_sync = 1;
	}
	spin_unlock(&sdp->sd_statfs_spin);

	brelse(l_bh);
	if (need_sync)
		gfs2_wake_up_statfs(sdp);
}