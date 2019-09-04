#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gfs2_sbd {scalar_t__ sd_log_flush_head; scalar_t__ sd_log_tail; scalar_t__ sd_log_head; TYPE_1__* sd_jdesc; } ;
struct TYPE_2__ {scalar_t__ jd_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static void gfs2_log_incr_head(struct gfs2_sbd *sdp)
{
	BUG_ON((sdp->sd_log_flush_head == sdp->sd_log_tail) &&
	       (sdp->sd_log_flush_head != sdp->sd_log_head));

	if (++sdp->sd_log_flush_head == sdp->sd_jdesc->jd_blocks)
		sdp->sd_log_flush_head = 0;
}