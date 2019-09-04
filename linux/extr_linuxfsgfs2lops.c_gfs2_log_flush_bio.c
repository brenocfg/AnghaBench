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
struct gfs2_sbd {int /*<<< orphan*/ * sd_log_bio; int /*<<< orphan*/  sd_log_in_flight; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_set_op_attrs (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  submit_bio (int /*<<< orphan*/ *) ; 

void gfs2_log_flush_bio(struct gfs2_sbd *sdp, int op, int op_flags)
{
	if (sdp->sd_log_bio) {
		atomic_inc(&sdp->sd_log_in_flight);
		bio_set_op_attrs(sdp->sd_log_bio, op, op_flags);
		submit_bio(sdp->sd_log_bio);
		sdp->sd_log_bio = NULL;
	}
}