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
struct dquot_warn {int dummy; } ;
struct TYPE_7__ {scalar_t__ dqb_curinodes; scalar_t__ dqb_ihardlimit; scalar_t__ dqb_isoftlimit; scalar_t__ dqb_itime; } ;
struct TYPE_6__ {size_t type; } ;
struct dquot {int /*<<< orphan*/  dq_dqb_lock; TYPE_3__ dq_dqb; TYPE_2__ dq_id; int /*<<< orphan*/  dq_sb; int /*<<< orphan*/  dq_flags; } ;
typedef  scalar_t__ qsize_t ;
struct TYPE_8__ {TYPE_1__* info; } ;
struct TYPE_5__ {scalar_t__ dqi_igrace; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQ_FAKE_B ; 
 int EDQUOT ; 
 int /*<<< orphan*/  QUOTA_NL_IHARDWARN ; 
 int /*<<< orphan*/  QUOTA_NL_ISOFTLONGWARN ; 
 int /*<<< orphan*/  QUOTA_NL_ISOFTWARN ; 
 int /*<<< orphan*/  ignore_hardlimit (struct dquot*) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  prepare_warning (struct dquot_warn*,struct dquot*,int /*<<< orphan*/ ) ; 
 TYPE_4__* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_has_quota_limits_enabled (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dquot_add_inodes(struct dquot *dquot, qsize_t inodes,
			    struct dquot_warn *warn)
{
	qsize_t newinodes;
	int ret = 0;

	spin_lock(&dquot->dq_dqb_lock);
	newinodes = dquot->dq_dqb.dqb_curinodes + inodes;
	if (!sb_has_quota_limits_enabled(dquot->dq_sb, dquot->dq_id.type) ||
	    test_bit(DQ_FAKE_B, &dquot->dq_flags))
		goto add;

	if (dquot->dq_dqb.dqb_ihardlimit &&
	    newinodes > dquot->dq_dqb.dqb_ihardlimit &&
            !ignore_hardlimit(dquot)) {
		prepare_warning(warn, dquot, QUOTA_NL_IHARDWARN);
		ret = -EDQUOT;
		goto out;
	}

	if (dquot->dq_dqb.dqb_isoftlimit &&
	    newinodes > dquot->dq_dqb.dqb_isoftlimit &&
	    dquot->dq_dqb.dqb_itime &&
	    ktime_get_real_seconds() >= dquot->dq_dqb.dqb_itime &&
            !ignore_hardlimit(dquot)) {
		prepare_warning(warn, dquot, QUOTA_NL_ISOFTLONGWARN);
		ret = -EDQUOT;
		goto out;
	}

	if (dquot->dq_dqb.dqb_isoftlimit &&
	    newinodes > dquot->dq_dqb.dqb_isoftlimit &&
	    dquot->dq_dqb.dqb_itime == 0) {
		prepare_warning(warn, dquot, QUOTA_NL_ISOFTWARN);
		dquot->dq_dqb.dqb_itime = ktime_get_real_seconds() +
		    sb_dqopt(dquot->dq_sb)->info[dquot->dq_id.type].dqi_igrace;
	}
add:
	dquot->dq_dqb.dqb_curinodes = newinodes;

out:
	spin_unlock(&dquot->dq_dqb_lock);
	return ret;
}