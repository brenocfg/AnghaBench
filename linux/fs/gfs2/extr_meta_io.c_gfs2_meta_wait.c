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
struct gfs2_trans {int /*<<< orphan*/  tr_flags; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {struct gfs2_trans* journal_info; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SDF_WITHDRAWN ; 
 int /*<<< orphan*/  TR_TOUCHED ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  gfs2_io_error_bh_wd (struct gfs2_sbd*,struct buffer_head*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int gfs2_meta_wait(struct gfs2_sbd *sdp, struct buffer_head *bh)
{
	if (unlikely(test_bit(SDF_WITHDRAWN, &sdp->sd_flags)))
		return -EIO;

	wait_on_buffer(bh);

	if (!buffer_uptodate(bh)) {
		struct gfs2_trans *tr = current->journal_info;
		if (tr && test_bit(TR_TOUCHED, &tr->tr_flags))
			gfs2_io_error_bh_wd(sdp, bh);
		return -EIO;
	}
	if (unlikely(test_bit(SDF_WITHDRAWN, &sdp->sd_flags)))
		return -EIO;

	return 0;
}