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
struct gfs2_sbd {int sd_log_error; int /*<<< orphan*/  sd_logd_waitq; int /*<<< orphan*/  sd_flags; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  SDF_WITHDRAWN ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,char const*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void quotad_error(struct gfs2_sbd *sdp, const char *msg, int error)
{
	if (error == 0 || error == -EROFS)
		return;
	if (!test_bit(SDF_WITHDRAWN, &sdp->sd_flags)) {
		fs_err(sdp, "gfs2_quotad: %s error %d\n", msg, error);
		sdp->sd_log_error = error;
		wake_up(&sdp->sd_logd_waitq);
	}
}