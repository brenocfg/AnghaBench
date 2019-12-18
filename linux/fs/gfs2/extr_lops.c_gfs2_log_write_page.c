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
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct page {int dummy; } ;
struct gfs2_sbd {struct super_block* sd_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_log_bmap (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_log_write (struct gfs2_sbd*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gfs2_log_write_page(struct gfs2_sbd *sdp, struct page *page)
{
	struct super_block *sb = sdp->sd_vfs;
	gfs2_log_write(sdp, page, sb->s_blocksize, 0,
		       gfs2_log_bmap(sdp));
}