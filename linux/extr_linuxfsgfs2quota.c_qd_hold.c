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
struct gfs2_sbd {int dummy; } ;
struct gfs2_quota_data {int /*<<< orphan*/  qd_lockref; TYPE_2__* qd_gl; } ;
struct TYPE_3__ {struct gfs2_sbd* ln_sbd; } ;
struct TYPE_4__ {TYPE_1__ gl_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lockref_is_dead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_assert (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  lockref_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qd_hold(struct gfs2_quota_data *qd)
{
	struct gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;
	gfs2_assert(sdp, !__lockref_is_dead(&qd->qd_lockref));
	lockref_get(&qd->qd_lockref);
}