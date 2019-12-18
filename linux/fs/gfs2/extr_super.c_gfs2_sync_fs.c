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
struct super_block {struct gfs2_sbd* s_fs_info; } ;
struct gfs2_sbd {int sd_log_error; } ;

/* Variables and functions */
 int GFS2_LFC_SYNC_FS ; 
 int GFS2_LOG_HEAD_FLUSH_NORMAL ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gfs2_quota_sync (struct super_block*,int) ; 

__attribute__((used)) static int gfs2_sync_fs(struct super_block *sb, int wait)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;

	gfs2_quota_sync(sb, -1);
	if (wait)
		gfs2_log_flush(sdp, NULL, GFS2_LOG_HEAD_FLUSH_NORMAL |
			       GFS2_LFC_SYNC_FS);
	return sdp->sd_log_error;
}