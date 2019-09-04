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
struct super_block {int dummy; } ;
struct dquot_warn {int dummy; } ;
struct TYPE_7__ {scalar_t__ dqb_curspace; scalar_t__ dqb_rsvspace; scalar_t__ dqb_bhardlimit; scalar_t__ dqb_bsoftlimit; scalar_t__ dqb_btime; } ;
struct TYPE_6__ {size_t type; } ;
struct dquot {int /*<<< orphan*/  dq_dqb_lock; TYPE_3__ dq_dqb; TYPE_2__ dq_id; int /*<<< orphan*/  dq_flags; struct super_block* dq_sb; } ;
typedef  scalar_t__ qsize_t ;
struct TYPE_8__ {TYPE_1__* info; } ;
struct TYPE_5__ {scalar_t__ dqi_bgrace; } ;

/* Variables and functions */
 unsigned int DQUOT_SPACE_NOFAIL ; 
 unsigned int DQUOT_SPACE_WARN ; 
 int /*<<< orphan*/  DQ_FAKE_B ; 
 int EDQUOT ; 
 int /*<<< orphan*/  QUOTA_NL_BHARDWARN ; 
 int /*<<< orphan*/  QUOTA_NL_BSOFTLONGWARN ; 
 int /*<<< orphan*/  QUOTA_NL_BSOFTWARN ; 
 int /*<<< orphan*/  ignore_hardlimit (struct dquot*) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  prepare_warning (struct dquot_warn*,struct dquot*,int /*<<< orphan*/ ) ; 
 TYPE_4__* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  sb_has_quota_limits_enabled (struct super_block*,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dquot_add_space(struct dquot *dquot, qsize_t space,
			   qsize_t rsv_space, unsigned int flags,
			   struct dquot_warn *warn)
{
	qsize_t tspace;
	struct super_block *sb = dquot->dq_sb;
	int ret = 0;

	spin_lock(&dquot->dq_dqb_lock);
	if (!sb_has_quota_limits_enabled(sb, dquot->dq_id.type) ||
	    test_bit(DQ_FAKE_B, &dquot->dq_flags))
		goto finish;

	tspace = dquot->dq_dqb.dqb_curspace + dquot->dq_dqb.dqb_rsvspace
		+ space + rsv_space;

	if (dquot->dq_dqb.dqb_bhardlimit &&
	    tspace > dquot->dq_dqb.dqb_bhardlimit &&
            !ignore_hardlimit(dquot)) {
		if (flags & DQUOT_SPACE_WARN)
			prepare_warning(warn, dquot, QUOTA_NL_BHARDWARN);
		ret = -EDQUOT;
		goto finish;
	}

	if (dquot->dq_dqb.dqb_bsoftlimit &&
	    tspace > dquot->dq_dqb.dqb_bsoftlimit &&
	    dquot->dq_dqb.dqb_btime &&
	    ktime_get_real_seconds() >= dquot->dq_dqb.dqb_btime &&
            !ignore_hardlimit(dquot)) {
		if (flags & DQUOT_SPACE_WARN)
			prepare_warning(warn, dquot, QUOTA_NL_BSOFTLONGWARN);
		ret = -EDQUOT;
		goto finish;
	}

	if (dquot->dq_dqb.dqb_bsoftlimit &&
	    tspace > dquot->dq_dqb.dqb_bsoftlimit &&
	    dquot->dq_dqb.dqb_btime == 0) {
		if (flags & DQUOT_SPACE_WARN) {
			prepare_warning(warn, dquot, QUOTA_NL_BSOFTWARN);
			dquot->dq_dqb.dqb_btime = ktime_get_real_seconds() +
			    sb_dqopt(sb)->info[dquot->dq_id.type].dqi_bgrace;
		} else {
			/*
			 * We don't allow preallocation to exceed softlimit so exceeding will
			 * be always printed
			 */
			ret = -EDQUOT;
			goto finish;
		}
	}
finish:
	/*
	 * We have to be careful and go through warning generation & grace time
	 * setting even if DQUOT_SPACE_NOFAIL is set. That's why we check it
	 * only here...
	 */
	if (flags & DQUOT_SPACE_NOFAIL)
		ret = 0;
	if (!ret) {
		dquot->dq_dqb.dqb_rsvspace += rsv_space;
		dquot->dq_dqb.dqb_curspace += space;
	}
	spin_unlock(&dquot->dq_dqb_lock);
	return ret;
}