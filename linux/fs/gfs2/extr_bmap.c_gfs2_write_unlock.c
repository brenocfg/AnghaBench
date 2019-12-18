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
struct inode {int dummy; } ;
struct gfs2_sbd {struct inode* sd_statfs_inode; int /*<<< orphan*/ * sd_rindex; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gh; int /*<<< orphan*/  i_inode; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfs2_write_unlock(struct inode *inode)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);

	if (&ip->i_inode == sdp->sd_rindex) {
		struct gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);

		gfs2_glock_dq_uninit(&m_ip->i_gh);
	}
	gfs2_glock_dq_uninit(&ip->i_gh);
}