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
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; } ;
struct buffer_head {scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDF_WITHDRAWN ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,unsigned long long,char const*,char*,unsigned int) ; 
 int /*<<< orphan*/  gfs2_lm_withdraw (struct gfs2_sbd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gfs2_io_error_bh_i(struct gfs2_sbd *sdp, struct buffer_head *bh,
			const char *function, char *file, unsigned int line,
			bool withdraw)
{
	if (!test_bit(SDF_WITHDRAWN, &sdp->sd_flags))
		fs_err(sdp,
		       "fatal: I/O error\n"
		       "  block = %llu\n"
		       "  function = %s, file = %s, line = %u\n",
		       (unsigned long long)bh->b_blocknr,
		       function, file, line);
	if (withdraw)
		gfs2_lm_withdraw(sdp, NULL);
}