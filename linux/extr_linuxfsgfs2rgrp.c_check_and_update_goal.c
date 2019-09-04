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
struct gfs2_inode {int /*<<< orphan*/  i_no_addr; int /*<<< orphan*/  i_goal; int /*<<< orphan*/  i_inode; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gfs2_blk2rgrpd (struct gfs2_sbd*,int /*<<< orphan*/ ,int) ; 

void check_and_update_goal(struct gfs2_inode *ip)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	if (!ip->i_goal || gfs2_blk2rgrpd(sdp, ip->i_goal, 1) == NULL)
		ip->i_goal = ip->i_no_addr;
}