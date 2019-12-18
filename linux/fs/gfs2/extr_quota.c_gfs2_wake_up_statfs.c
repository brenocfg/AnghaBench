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
struct gfs2_sbd {int sd_statfs_force_sync; int /*<<< orphan*/  sd_quota_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void gfs2_wake_up_statfs(struct gfs2_sbd *sdp) {
	if (!sdp->sd_statfs_force_sync) {
		sdp->sd_statfs_force_sync = 1;
		wake_up(&sdp->sd_quota_wait);
	}
}