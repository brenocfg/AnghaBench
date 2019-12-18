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
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ctime; } ;
struct gfs2_inode {scalar_t__ i_entries; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry const*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int gfs2_dir_del (struct gfs2_inode*,struct dentry const*) ; 
 int /*<<< orphan*/  gfs2_unlink_di (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static int gfs2_unlink_inode(struct gfs2_inode *dip,
			     const struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);
	struct gfs2_inode *ip = GFS2_I(inode);
	int error;

	error = gfs2_dir_del(dip, dentry);
	if (error)
		return error;

	ip->i_entries = 0;
	inode->i_ctime = current_time(inode);
	if (S_ISDIR(inode->i_mode))
		clear_nlink(inode);
	else
		drop_nlink(inode);
	mark_inode_dirty(inode);
	if (inode->i_nlink == 0)
		gfs2_unlink_di(inode);
	return 0;
}