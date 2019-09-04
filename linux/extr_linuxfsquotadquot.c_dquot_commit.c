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
struct quota_info {TYPE_2__** ops; } ;
struct TYPE_3__ {size_t type; } ;
struct dquot {int /*<<< orphan*/  dq_lock; TYPE_1__ dq_id; int /*<<< orphan*/  dq_flags; int /*<<< orphan*/  dq_sb; } ;
struct TYPE_4__ {int (* commit_dqblk ) (struct dquot*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DQ_ACTIVE_B ; 
 int EIO ; 
 int /*<<< orphan*/  clear_dquot_dirty (struct dquot*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct quota_info* sb_dqopt (int /*<<< orphan*/ ) ; 
 int stub1 (struct dquot*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dquot_commit(struct dquot *dquot)
{
	int ret = 0;
	struct quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	mutex_lock(&dquot->dq_lock);
	if (!clear_dquot_dirty(dquot))
		goto out_lock;
	/* Inactive dquot can be only if there was error during read/init
	 * => we have better not writing it */
	if (test_bit(DQ_ACTIVE_B, &dquot->dq_flags))
		ret = dqopt->ops[dquot->dq_id.type]->commit_dqblk(dquot);
	else
		ret = -EIO;
out_lock:
	mutex_unlock(&dquot->dq_lock);
	return ret;
}