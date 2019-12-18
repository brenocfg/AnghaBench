#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {int sb_bsize_shift; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
struct gfs2_jdesc {int jd_blocks; int /*<<< orphan*/  jd_inode; } ;
struct gfs2_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EIO ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ gfs2_check_internal_file_size (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 scalar_t__ gfs2_write_alloc_required (struct gfs2_inode*,int /*<<< orphan*/ ,int) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 

int gfs2_jdesc_check(struct gfs2_jdesc *jd)
{
	struct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	struct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	u64 size = i_size_read(jd->jd_inode);

	if (gfs2_check_internal_file_size(jd->jd_inode, 8 << 20, BIT(30)))
		return -EIO;

	jd->jd_blocks = size >> sdp->sd_sb.sb_bsize_shift;

	if (gfs2_write_alloc_required(ip, 0, size)) {
		gfs2_consist_inode(ip);
		return -EIO;
	}

	return 0;
}