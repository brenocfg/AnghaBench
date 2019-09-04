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
struct gfs2_sb_host {scalar_t__ sb_magic; scalar_t__ sb_type; scalar_t__ sb_fs_format; scalar_t__ sb_multihost_format; } ;
struct gfs2_sbd {struct gfs2_sb_host sd_sb; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GFS2_FORMAT_FS ; 
 scalar_t__ GFS2_FORMAT_MULTI ; 
 scalar_t__ GFS2_MAGIC ; 
 scalar_t__ GFS2_METATYPE_SB ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int gfs2_check_sb(struct gfs2_sbd *sdp, int silent)
{
	struct gfs2_sb_host *sb = &sdp->sd_sb;

	if (sb->sb_magic != GFS2_MAGIC ||
	    sb->sb_type != GFS2_METATYPE_SB) {
		if (!silent)
			pr_warn("not a GFS2 filesystem\n");
		return -EINVAL;
	}

	/*  If format numbers match exactly, we're done.  */

	if (sb->sb_fs_format == GFS2_FORMAT_FS &&
	    sb->sb_multihost_format == GFS2_FORMAT_MULTI)
		return 0;

	fs_warn(sdp, "Unknown on-disk format, unable to mount\n");

	return -EINVAL;
}