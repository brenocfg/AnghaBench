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
struct quota_info {TYPE_1__** ops; int /*<<< orphan*/ * info; } ;
struct TYPE_4__ {size_t type; } ;
struct dquot {int /*<<< orphan*/  dq_lock; int /*<<< orphan*/  dq_flags; TYPE_2__ dq_id; int /*<<< orphan*/  dq_sb; int /*<<< orphan*/  dq_off; } ;
struct TYPE_3__ {int (* read_dqblk ) (struct dquot*) ;int (* commit_dqblk ) (struct dquot*) ;int (* write_file_info ) (int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DQ_ACTIVE_B ; 
 int /*<<< orphan*/  DQ_READ_B ; 
 scalar_t__ info_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct quota_info* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int stub1 (struct dquot*) ; 
 int stub2 (struct dquot*) ; 
 int stub3 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dquot_acquire(struct dquot *dquot)
{
	int ret = 0, ret2 = 0;
	struct quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	mutex_lock(&dquot->dq_lock);
	if (!test_bit(DQ_READ_B, &dquot->dq_flags)) {
		ret = dqopt->ops[dquot->dq_id.type]->read_dqblk(dquot);
		if (ret < 0)
			goto out_iolock;
	}
	/* Make sure flags update is visible after dquot has been filled */
	smp_mb__before_atomic();
	set_bit(DQ_READ_B, &dquot->dq_flags);
	/* Instantiate dquot if needed */
	if (!test_bit(DQ_ACTIVE_B, &dquot->dq_flags) && !dquot->dq_off) {
		ret = dqopt->ops[dquot->dq_id.type]->commit_dqblk(dquot);
		/* Write the info if needed */
		if (info_dirty(&dqopt->info[dquot->dq_id.type])) {
			ret2 = dqopt->ops[dquot->dq_id.type]->write_file_info(
					dquot->dq_sb, dquot->dq_id.type);
		}
		if (ret < 0)
			goto out_iolock;
		if (ret2 < 0) {
			ret = ret2;
			goto out_iolock;
		}
	}
	/*
	 * Make sure flags update is visible after on-disk struct has been
	 * allocated. Paired with smp_rmb() in dqget().
	 */
	smp_mb__before_atomic();
	set_bit(DQ_ACTIVE_B, &dquot->dq_flags);
out_iolock:
	mutex_unlock(&dquot->dq_lock);
	return ret;
}