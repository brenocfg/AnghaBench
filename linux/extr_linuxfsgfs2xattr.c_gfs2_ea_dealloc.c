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
struct gfs2_inode {int i_diskflags; int /*<<< orphan*/  i_inode; } ;

/* Variables and functions */
 int GFS2_DIF_EA_INDIRECT ; 
 int /*<<< orphan*/  GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_GID_QUOTA_CHANGE ; 
 int /*<<< orphan*/  NO_UID_QUOTA_CHANGE ; 
 int ea_dealloc_block (struct gfs2_inode*) ; 
 int ea_dealloc_indirect (struct gfs2_inode*) ; 
 int /*<<< orphan*/  ea_dealloc_unstuffed ; 
 int ea_foreach (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gfs2_quota_hold (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_quota_unhold (struct gfs2_inode*) ; 
 int gfs2_rindex_update (int /*<<< orphan*/ ) ; 

int gfs2_ea_dealloc(struct gfs2_inode *ip)
{
	int error;

	error = gfs2_rindex_update(GFS2_SB(&ip->i_inode));
	if (error)
		return error;

	error = gfs2_quota_hold(ip, NO_UID_QUOTA_CHANGE, NO_GID_QUOTA_CHANGE);
	if (error)
		return error;

	error = ea_foreach(ip, ea_dealloc_unstuffed, NULL);
	if (error)
		goto out_quota;

	if (ip->i_diskflags & GFS2_DIF_EA_INDIRECT) {
		error = ea_dealloc_indirect(ip);
		if (error)
			goto out_quota;
	}

	error = ea_dealloc_block(ip);

out_quota:
	gfs2_quota_unhold(ip);
	return error;
}