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
struct gfs2_quota_data {int /*<<< orphan*/  qd_flags; TYPE_2__* qd_gl; } ;
struct TYPE_3__ {int /*<<< orphan*/  ln_sbd; } ;
struct TYPE_4__ {TYPE_1__ gl_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  QDF_LOCKED ; 
 int /*<<< orphan*/  bh_put (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_assert_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qd_put (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  slot_put (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qd_unlock(struct gfs2_quota_data *qd)
{
	gfs2_assert_warn(qd->qd_gl->gl_name.ln_sbd,
			 test_bit(QDF_LOCKED, &qd->qd_flags));
	clear_bit(QDF_LOCKED, &qd->qd_flags);
	bh_put(qd);
	slot_put(qd);
	qd_put(qd);
}