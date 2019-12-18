#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_5__ {scalar_t__ ar_quota; } ;
struct gfs2_sbd {TYPE_4__* sd_vfs; TYPE_1__ sd_args; } ;
struct TYPE_7__ {int /*<<< orphan*/  qb_value; int /*<<< orphan*/  qb_limit; int /*<<< orphan*/  qb_warn; } ;
struct gfs2_quota_data {scalar_t__ qd_change; scalar_t__ qd_last_warn; int /*<<< orphan*/  qd_id; int /*<<< orphan*/  qd_flags; TYPE_3__ qd_qb; } ;
struct gfs2_inode {TYPE_2__* i_qadata; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_inode; } ;
struct gfs2_alloc_parms {scalar_t__ allowed; scalar_t__ min_target; scalar_t__ target; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
struct TYPE_8__ {int /*<<< orphan*/  s_dev; } ;
struct TYPE_6__ {size_t qa_qd_num; struct gfs2_quota_data** qa_qd; } ;

/* Variables and functions */
 int EDQUOT ; 
 scalar_t__ GFS2_QUOTA_ON ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIF_QD_LOCKED ; 
 int HZ ; 
 int /*<<< orphan*/  QDF_QMSG_QUIET ; 
 int /*<<< orphan*/  QUOTA_NL_BHARDWARN ; 
 int /*<<< orphan*/  QUOTA_NL_BSOFTWARN ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int gfs2_tune_get (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gt_quota_warn_period ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  make_kqid_gid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kqid_uid (int /*<<< orphan*/ ) ; 
 int print_message (struct gfs2_quota_data*,char*) ; 
 int /*<<< orphan*/  qd_lock ; 
 scalar_t__ qid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quota_send_warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 

int gfs2_quota_check(struct gfs2_inode *ip, kuid_t uid, kgid_t gid,
		     struct gfs2_alloc_parms *ap)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_quota_data *qd;
	s64 value, warn, limit;
	u32 x;
	int error = 0;

	ap->allowed = UINT_MAX; /* Assume we are permitted a whole lot */
	if (!test_bit(GIF_QD_LOCKED, &ip->i_flags))
		return 0;

        if (sdp->sd_args.ar_quota != GFS2_QUOTA_ON)
                return 0;

	for (x = 0; x < ip->i_qadata->qa_qd_num; x++) {
		qd = ip->i_qadata->qa_qd[x];

		if (!(qid_eq(qd->qd_id, make_kqid_uid(uid)) ||
		      qid_eq(qd->qd_id, make_kqid_gid(gid))))
			continue;

		warn = (s64)be64_to_cpu(qd->qd_qb.qb_warn);
		limit = (s64)be64_to_cpu(qd->qd_qb.qb_limit);
		value = (s64)be64_to_cpu(qd->qd_qb.qb_value);
		spin_lock(&qd_lock);
		value += qd->qd_change;
		spin_unlock(&qd_lock);

		if (limit > 0 && (limit - value) < ap->allowed)
			ap->allowed = limit - value;
		/* If we can't meet the target */
		if (limit && limit < (value + (s64)ap->target)) {
			/* If no min_target specified or we don't meet
			 * min_target, return -EDQUOT */
			if (!ap->min_target || ap->min_target > ap->allowed) {
				if (!test_and_set_bit(QDF_QMSG_QUIET,
						      &qd->qd_flags)) {
					print_message(qd, "exceeded");
					quota_send_warning(qd->qd_id,
							   sdp->sd_vfs->s_dev,
							   QUOTA_NL_BHARDWARN);
				}
				error = -EDQUOT;
				break;
			}
		} else if (warn && warn < value &&
			   time_after_eq(jiffies, qd->qd_last_warn +
					 gfs2_tune_get(sdp, gt_quota_warn_period)
					 * HZ)) {
			quota_send_warning(qd->qd_id,
					   sdp->sd_vfs->s_dev, QUOTA_NL_BSOFTWARN);
			error = print_message(qd, "warning");
			qd->qd_last_warn = jiffies;
		}
	}
	return error;
}