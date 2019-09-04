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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_inode; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_CREATE ; 
 int /*<<< orphan*/  REMOVE_META ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* gfs2_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_log_lock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_log_unlock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_remove_from_journal (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

void gfs2_meta_wipe(struct gfs2_inode *ip, u64 bstart, u32 blen)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct buffer_head *bh;

	while (blen) {
		bh = gfs2_getbuf(ip->i_gl, bstart, NO_CREATE);
		if (bh) {
			lock_buffer(bh);
			gfs2_log_lock(sdp);
			gfs2_remove_from_journal(bh, REMOVE_META);
			gfs2_log_unlock(sdp);
			unlock_buffer(bh);
			brelse(bh);
		}

		bstart++;
		blen--;
	}
}