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
struct gfs2_rgrpd {unsigned long long rd_length; unsigned long long rd_data; unsigned long long rd_bitbytes; scalar_t__ rd_data0; scalar_t__ rd_addr; struct gfs2_sbd* rd_sbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*,unsigned long long) ; 

__attribute__((used)) static void gfs2_rindex_print(const struct gfs2_rgrpd *rgd)
{
	struct gfs2_sbd *sdp = rgd->rd_sbd;

	fs_info(sdp, "ri_addr = %llu\n", (unsigned long long)rgd->rd_addr);
	fs_info(sdp, "ri_length = %u\n", rgd->rd_length);
	fs_info(sdp, "ri_data0 = %llu\n", (unsigned long long)rgd->rd_data0);
	fs_info(sdp, "ri_data = %u\n", rgd->rd_data);
	fs_info(sdp, "ri_bitbytes = %u\n", rgd->rd_bitbytes);
}