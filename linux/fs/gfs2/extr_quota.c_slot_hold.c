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
struct gfs2_sbd {int /*<<< orphan*/  sd_bitmap_lock; } ;
struct gfs2_quota_data {int /*<<< orphan*/  qd_slot_count; struct gfs2_sbd* qd_sbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_assert (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void slot_hold(struct gfs2_quota_data *qd)
{
	struct gfs2_sbd *sdp = qd->qd_sbd;

	spin_lock(&sdp->sd_bitmap_lock);
	gfs2_assert(sdp, qd->qd_slot_count);
	qd->qd_slot_count++;
	spin_unlock(&sdp->sd_bitmap_lock);
}