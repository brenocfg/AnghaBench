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
struct fuse_conn {int dev; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct dentry* s_root; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fuse_conn_congestion_threshold_ops ; 
 int /*<<< orphan*/  fuse_conn_max_background_ops ; 
 TYPE_1__* fuse_control_sb ; 
 int /*<<< orphan*/  fuse_ctl_abort_ops ; 
 struct dentry* fuse_ctl_add_dentry (struct dentry*,struct fuse_conn*,char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_ctl_remove_conn (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_ctl_waiting_ops ; 
 int /*<<< orphan*/  inc_nlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int fuse_ctl_add_conn(struct fuse_conn *fc)
{
	struct dentry *parent;
	char name[32];

	if (!fuse_control_sb)
		return 0;

	parent = fuse_control_sb->s_root;
	inc_nlink(d_inode(parent));
	sprintf(name, "%u", fc->dev);
	parent = fuse_ctl_add_dentry(parent, fc, name, S_IFDIR | 0500, 2,
				     &simple_dir_inode_operations,
				     &simple_dir_operations);
	if (!parent)
		goto err;

	if (!fuse_ctl_add_dentry(parent, fc, "waiting", S_IFREG | 0400, 1,
				 NULL, &fuse_ctl_waiting_ops) ||
	    !fuse_ctl_add_dentry(parent, fc, "abort", S_IFREG | 0200, 1,
				 NULL, &fuse_ctl_abort_ops) ||
	    !fuse_ctl_add_dentry(parent, fc, "max_background", S_IFREG | 0600,
				 1, NULL, &fuse_conn_max_background_ops) ||
	    !fuse_ctl_add_dentry(parent, fc, "congestion_threshold",
				 S_IFREG | 0600, 1, NULL,
				 &fuse_conn_congestion_threshold_ops))
		goto err;

	return 0;

 err:
	fuse_ctl_remove_conn(fc);
	return -ENOMEM;
}