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
struct gfs2_rgrpd {scalar_t__ rd_addr; struct gfs2_sbd* rd_sbd; } ;

/* Variables and functions */
 int gfs2_lm_withdraw (struct gfs2_sbd*,char*,unsigned long long,char const*,char*,unsigned int) ; 

int gfs2_consist_rgrpd_i(struct gfs2_rgrpd *rgd, int cluster_wide,
			 const char *function, char *file, unsigned int line)
{
	struct gfs2_sbd *sdp = rgd->rd_sbd;
	int rv;
	rv = gfs2_lm_withdraw(sdp,
			      "fatal: filesystem consistency error\n"
			      "  RG = %llu\n"
			      "  function = %s, file = %s, line = %u\n",
			      (unsigned long long)rgd->rd_addr,
			      function, file, line);
	return rv;
}