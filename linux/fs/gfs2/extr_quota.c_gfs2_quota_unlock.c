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
typedef  size_t u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_quota_data {int /*<<< orphan*/  qd_flags; int /*<<< orphan*/  qd_change_sync; } ;
struct gfs2_inode {TYPE_1__* i_qadata; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_inode; } ;
struct TYPE_2__ {size_t qa_qd_num; int /*<<< orphan*/ * qa_qd_ghs; struct gfs2_quota_data** qa_qd; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIF_QD_LOCKED ; 
 int /*<<< orphan*/  QDF_LOCKED ; 
 scalar_t__ bh_get (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_sync (unsigned int,struct gfs2_quota_data**) ; 
 int /*<<< orphan*/  gfs2_assert_warn (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_quota_unhold (struct gfs2_inode*) ; 
 int need_sync (struct gfs2_quota_data*) ; 
 int qd_check_sync (struct gfs2_sbd*,struct gfs2_quota_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qd_lock ; 
 int /*<<< orphan*/  qd_put (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  qd_unlock (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  slot_put (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gfs2_quota_unlock(struct gfs2_inode *ip)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_quota_data *qda[4];
	unsigned int count = 0;
	u32 x;
	int found;

	if (!test_and_clear_bit(GIF_QD_LOCKED, &ip->i_flags))
		goto out;

	for (x = 0; x < ip->i_qadata->qa_qd_num; x++) {
		struct gfs2_quota_data *qd;
		int sync;

		qd = ip->i_qadata->qa_qd[x];
		sync = need_sync(qd);

		gfs2_glock_dq_uninit(&ip->i_qadata->qa_qd_ghs[x]);
		if (!sync)
			continue;

		spin_lock(&qd_lock);
		found = qd_check_sync(sdp, qd, NULL);
		spin_unlock(&qd_lock);

		if (!found)
			continue;

		gfs2_assert_warn(sdp, qd->qd_change_sync);
		if (bh_get(qd)) {
			clear_bit(QDF_LOCKED, &qd->qd_flags);
			slot_put(qd);
			qd_put(qd);
			continue;
		}

		qda[count++] = qd;
	}

	if (count) {
		do_sync(count, qda);
		for (x = 0; x < count; x++)
			qd_unlock(qda[x]);
	}

out:
	gfs2_quota_unhold(ip);
}