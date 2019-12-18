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
struct gfs2_sbd {char* sd_fsname; } ;
struct gfs2_rgrpd {int /*<<< orphan*/  rd_flags; int /*<<< orphan*/  rd_gl; scalar_t__ rd_addr; struct gfs2_sbd* rd_sbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_RDF_ERROR ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*,...) ; 
 int /*<<< orphan*/  gfs2_rgrp_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static void gfs2_rgrp_error(struct gfs2_rgrpd *rgd)
{
	struct gfs2_sbd *sdp = rgd->rd_sbd;
	char fs_id_buf[sizeof(sdp->sd_fsname) + 7];

	fs_warn(sdp, "rgrp %llu has an error, marking it readonly until umount\n",
		(unsigned long long)rgd->rd_addr);
	fs_warn(sdp, "umount on all nodes and run fsck.gfs2 to fix the error\n");
	sprintf(fs_id_buf, "fsid=%s: ", sdp->sd_fsname);
	gfs2_rgrp_dump(NULL, rgd->rd_gl, fs_id_buf);
	rgd->rd_flags |= GFS2_RDF_ERROR;
}