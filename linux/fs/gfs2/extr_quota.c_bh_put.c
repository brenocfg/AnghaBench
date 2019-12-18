#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gfs2_sbd {int /*<<< orphan*/  sd_quota_mutex; } ;
struct gfs2_quota_data {int /*<<< orphan*/ * qd_bh_qc; int /*<<< orphan*/ * qd_bh; int /*<<< orphan*/  qd_bh_count; TYPE_2__* qd_gl; } ;
struct TYPE_3__ {struct gfs2_sbd* ln_sbd; } ;
struct TYPE_4__ {TYPE_1__ gl_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_assert (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bh_put(struct gfs2_quota_data *qd)
{
	struct gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;

	mutex_lock(&sdp->sd_quota_mutex);
	gfs2_assert(sdp, qd->qd_bh_count);
	if (!--qd->qd_bh_count) {
		brelse(qd->qd_bh);
		qd->qd_bh = NULL;
		qd->qd_bh_qc = NULL;
	}
	mutex_unlock(&sdp->sd_quota_mutex);
}