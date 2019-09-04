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
struct gfs2_inode {int /*<<< orphan*/  i_eattr; } ;
struct gfs2_ea_location {int /*<<< orphan*/  el_bh; int /*<<< orphan*/  el_prev; int /*<<< orphan*/  el_ea; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ GFS2_EA_IS_STUFFED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int ea_remove_stuffed (struct gfs2_inode*,struct gfs2_ea_location*) ; 
 int ea_remove_unstuffed (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gfs2_ea_find (struct gfs2_inode*,int,char const*,struct gfs2_ea_location*) ; 

__attribute__((used)) static int gfs2_xattr_remove(struct gfs2_inode *ip, int type, const char *name)
{
	struct gfs2_ea_location el;
	int error;

	if (!ip->i_eattr)
		return -ENODATA;

	error = gfs2_ea_find(ip, type, name, &el);
	if (error)
		return error;
	if (!el.el_ea)
		return -ENODATA;

	if (GFS2_EA_IS_STUFFED(el.el_ea))
		error = ea_remove_stuffed(ip, &el);
	else
		error = ea_remove_unstuffed(ip, el.el_bh, el.el_ea, el.el_prev, 0);

	brelse(el.el_bh);

	return error;
}