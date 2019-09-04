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
struct gfs2_inode {int /*<<< orphan*/  i_inode; } ;
struct gfs2_ea_header {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_GID_QUOTA_CHANGE ; 
 int /*<<< orphan*/  NO_UID_QUOTA_CHANGE ; 
 int ea_dealloc_unstuffed (struct gfs2_inode*,struct buffer_head*,struct gfs2_ea_header*,struct gfs2_ea_header*,int*) ; 
 int gfs2_quota_hold (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_quota_unhold (struct gfs2_inode*) ; 
 int gfs2_rindex_update (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ea_remove_unstuffed(struct gfs2_inode *ip, struct buffer_head *bh,
			       struct gfs2_ea_header *ea,
			       struct gfs2_ea_header *prev, int leave)
{
	int error;

	error = gfs2_rindex_update(GFS2_SB(&ip->i_inode));
	if (error)
		return error;

	error = gfs2_quota_hold(ip, NO_UID_QUOTA_CHANGE, NO_GID_QUOTA_CHANGE);
	if (error)
		goto out_alloc;

	error = ea_dealloc_unstuffed(ip, bh, ea, prev, (leave) ? &error : NULL);

	gfs2_quota_unhold(ip);
out_alloc:
	return error;
}