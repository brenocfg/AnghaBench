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
struct gfs2_jdesc {int jd_recover_error; int /*<<< orphan*/  jd_flags; int /*<<< orphan*/  jd_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  JDF_RECOVERY ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  gfs_recovery_wq ; 
 int queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gfs2_recover_journal(struct gfs2_jdesc *jd, bool wait)
{
	int rv;

	if (test_and_set_bit(JDF_RECOVERY, &jd->jd_flags))
		return -EBUSY;

	/* we have JDF_RECOVERY, queue should always succeed */
	rv = queue_work(gfs_recovery_wq, &jd->jd_work);
	BUG_ON(!rv);

	if (wait)
		wait_on_bit(&jd->jd_flags, JDF_RECOVERY,
			    TASK_UNINTERRUPTIBLE);

	return wait ? jd->jd_recover_error : 0;
}