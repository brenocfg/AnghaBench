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
struct gfs2_inode {int /*<<< orphan*/  i_gh; int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_inode; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  GL_NOCACHE ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  gfs2_glock_dq (int /*<<< orphan*/ *) ; 
 int gfs2_glock_nq (int /*<<< orphan*/ *) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfs2_write_lock(struct inode *inode)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	int error;

	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &ip->i_gh);
	error = gfs2_glock_nq(&ip->i_gh);
	if (error)
		goto out_uninit;
	if (&ip->i_inode == sdp->sd_rindex) {
		struct gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);

		error = gfs2_glock_nq_init(m_ip->i_gl, LM_ST_EXCLUSIVE,
					   GL_NOCACHE, &m_ip->i_gh);
		if (error)
			goto out_unlock;
	}
	return 0;

out_unlock:
	gfs2_glock_dq(&ip->i_gh);
out_uninit:
	gfs2_holder_uninit(&ip->i_gh);
	return error;
}