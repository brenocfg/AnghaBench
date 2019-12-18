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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct gfs2_inode {TYPE_1__ i_inode; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (TYPE_1__*) ; 
 int /*<<< orphan*/  __gfs2_free_blocks (struct gfs2_inode*,struct gfs2_rgrpd*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  gfs2_quota_change (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_statfs_change (struct gfs2_sbd*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void gfs2_free_meta(struct gfs2_inode *ip, struct gfs2_rgrpd *rgd,
		    u64 bstart, u32 blen)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	__gfs2_free_blocks(ip, rgd, bstart, blen, 1);
	gfs2_statfs_change(sdp, 0, +blen, 0);
	gfs2_quota_change(ip, -(s64)blen, ip->i_inode.i_uid, ip->i_inode.i_gid);
}