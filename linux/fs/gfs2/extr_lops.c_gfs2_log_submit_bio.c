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
struct gfs2_sbd {int /*<<< orphan*/  sd_log_in_flight; } ;
struct bio {int bi_opf; struct gfs2_sbd* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

void gfs2_log_submit_bio(struct bio **biop, int opf)
{
	struct bio *bio = *biop;
	if (bio) {
		struct gfs2_sbd *sdp = bio->bi_private;
		atomic_inc(&sdp->sd_log_in_flight);
		bio->bi_opf = opf;
		submit_bio(bio);
		*biop = NULL;
	}
}