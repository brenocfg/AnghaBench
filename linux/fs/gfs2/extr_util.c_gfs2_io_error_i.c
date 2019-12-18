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
struct gfs2_sbd {int dummy; } ;

/* Variables and functions */
 int gfs2_lm_withdraw (struct gfs2_sbd*,char*,char const*,char*,unsigned int) ; 

int gfs2_io_error_i(struct gfs2_sbd *sdp, const char *function, char *file,
		    unsigned int line)
{
	int rv;
	rv = gfs2_lm_withdraw(sdp,
			      "fatal: I/O error\n"
			      "  function = %s, file = %s, line = %u\n",
			      function, file, line);
	return rv;
}