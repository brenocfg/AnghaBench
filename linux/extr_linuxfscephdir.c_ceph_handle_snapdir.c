#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; int /*<<< orphan*/  d_parent; int /*<<< orphan*/  d_sb; } ;
struct ceph_mds_request {int dummy; } ;
struct ceph_fs_client {TYPE_1__* mount_options; } ;
struct TYPE_3__ {int /*<<< orphan*/  snapdir_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CEPH_NOSNAP ; 
 int ENOENT ; 
 struct inode* ceph_get_snapdir (struct inode*) ; 
 struct ceph_fs_client* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,struct dentry*,struct inode*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ceph_handle_snapdir(struct ceph_mds_request *req,
			struct dentry *dentry, int err)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(dentry->d_sb);
	struct inode *parent = d_inode(dentry->d_parent); /* we hold i_mutex */

	/* .snap dir? */
	if (err == -ENOENT &&
	    ceph_snap(parent) == CEPH_NOSNAP &&
	    strcmp(dentry->d_name.name,
		   fsc->mount_options->snapdir_name) == 0) {
		struct inode *inode = ceph_get_snapdir(parent);
		dout("ENOENT on snapdir %p '%pd', linking to snapdir %p\n",
		     dentry, dentry, inode);
		BUG_ON(!d_unhashed(dentry));
		d_add(dentry, inode);
		err = 0;
	}
	return err;
}