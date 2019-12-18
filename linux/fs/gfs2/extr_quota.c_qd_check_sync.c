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
typedef  scalar_t__ u64 ;
struct gfs2_sbd {int /*<<< orphan*/  sd_quota_list; } ;
struct gfs2_quota_data {scalar_t__ qd_sync_gen; int /*<<< orphan*/  qd_change; int /*<<< orphan*/  qd_change_sync; int /*<<< orphan*/  qd_flags; int /*<<< orphan*/  qd_list; int /*<<< orphan*/  qd_lockref; } ;

/* Variables and functions */
 int /*<<< orphan*/  QDF_CHANGE ; 
 int /*<<< orphan*/  QDF_LOCKED ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockref_get_not_dead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slot_hold (struct gfs2_quota_data*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qd_check_sync(struct gfs2_sbd *sdp, struct gfs2_quota_data *qd,
			 u64 *sync_gen)
{
	if (test_bit(QDF_LOCKED, &qd->qd_flags) ||
	    !test_bit(QDF_CHANGE, &qd->qd_flags) ||
	    (sync_gen && (qd->qd_sync_gen >= *sync_gen)))
		return 0;

	if (!lockref_get_not_dead(&qd->qd_lockref))
		return 0;

	list_move_tail(&qd->qd_list, &sdp->sd_quota_list);
	set_bit(QDF_LOCKED, &qd->qd_flags);
	qd->qd_change_sync = qd->qd_change;
	slot_hold(qd);
	return 1;
}