#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gfs2_sbd {int /*<<< orphan*/  sd_quota_inode; } ;
struct gfs2_quota_lvb {scalar_t__ qb_magic; } ;
struct gfs2_quota_data {TYPE_3__* qd_gl; struct gfs2_quota_lvb qd_qb; int /*<<< orphan*/  qd_flags; } ;
struct gfs2_inode {TYPE_3__* i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct TYPE_5__ {scalar_t__ sb_lvbptr; } ;
struct TYPE_4__ {struct gfs2_sbd* ln_sbd; } ;
struct TYPE_6__ {TYPE_2__ gl_lksb; TYPE_1__ gl_name; } ;

/* Variables and functions */
 int FORCE ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFS2_MAGIC ; 
 int /*<<< orphan*/  GL_NOCACHE ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  QDF_REFRESH ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int update_qd (struct gfs2_sbd*,struct gfs2_quota_data*) ; 

__attribute__((used)) static int do_glock(struct gfs2_quota_data *qd, int force_refresh,
		    struct gfs2_holder *q_gh)
{
	struct gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;
	struct gfs2_inode *ip = GFS2_I(sdp->sd_quota_inode);
	struct gfs2_holder i_gh;
	int error;

restart:
	error = gfs2_glock_nq_init(qd->qd_gl, LM_ST_SHARED, 0, q_gh);
	if (error)
		return error;

	if (test_and_clear_bit(QDF_REFRESH, &qd->qd_flags))
		force_refresh = FORCE;

	qd->qd_qb = *(struct gfs2_quota_lvb *)qd->qd_gl->gl_lksb.sb_lvbptr;

	if (force_refresh || qd->qd_qb.qb_magic != cpu_to_be32(GFS2_MAGIC)) {
		gfs2_glock_dq_uninit(q_gh);
		error = gfs2_glock_nq_init(qd->qd_gl, LM_ST_EXCLUSIVE,
					   GL_NOCACHE, q_gh);
		if (error)
			return error;

		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, 0, &i_gh);
		if (error)
			goto fail;

		error = update_qd(sdp, qd);
		if (error)
			goto fail_gunlock;

		gfs2_glock_dq_uninit(&i_gh);
		gfs2_glock_dq_uninit(q_gh);
		force_refresh = 0;
		goto restart;
	}

	return 0;

fail_gunlock:
	gfs2_glock_dq_uninit(&i_gh);
fail:
	gfs2_glock_dq_uninit(q_gh);
	return error;
}