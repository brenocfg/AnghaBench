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
struct writeback_control {scalar_t__ sync_mode; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int GFS2_LFC_JDATA_WPAGES ; 
 int GFS2_LOG_HEAD_FLUSH_NORMAL ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,int /*<<< orphan*/ ,int) ; 
 int gfs2_write_cache_jdata (struct address_space*,struct writeback_control*) ; 

__attribute__((used)) static int gfs2_jdata_writepages(struct address_space *mapping,
				 struct writeback_control *wbc)
{
	struct gfs2_inode *ip = GFS2_I(mapping->host);
	struct gfs2_sbd *sdp = GFS2_SB(mapping->host);
	int ret;

	ret = gfs2_write_cache_jdata(mapping, wbc);
	if (ret == 0 && wbc->sync_mode == WB_SYNC_ALL) {
		gfs2_log_flush(sdp, ip->i_gl, GFS2_LOG_HEAD_FLUSH_NORMAL |
			       GFS2_LFC_JDATA_WPAGES);
		ret = gfs2_write_cache_jdata(mapping, wbc);
	}
	return ret;
}