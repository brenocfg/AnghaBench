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
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct dentry {int /*<<< orphan*/  d_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 int d_count (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_rehash (struct dentry*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*) ; 
 int nfs_safe_remove (struct dentry*) ; 
 int /*<<< orphan*/  nfs_save_change_attribute (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_verifier (struct dentry*,int /*<<< orphan*/ ) ; 
 int nfs_sillyrename (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfs_unlink_enter (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  trace_nfs_unlink_exit (struct inode*,struct dentry*,int) ; 
 int /*<<< orphan*/  write_inode_now (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfs_unlink(struct inode *dir, struct dentry *dentry)
{
	int error;
	int need_rehash = 0;

	dfprintk(VFS, "NFS: unlink(%s/%lu, %pd)\n", dir->i_sb->s_id,
		dir->i_ino, dentry);

	trace_nfs_unlink_enter(dir, dentry);
	spin_lock(&dentry->d_lock);
	if (d_count(dentry) > 1) {
		spin_unlock(&dentry->d_lock);
		/* Start asynchronous writeout of the inode */
		write_inode_now(d_inode(dentry), 0);
		error = nfs_sillyrename(dir, dentry);
		goto out;
	}
	if (!d_unhashed(dentry)) {
		__d_drop(dentry);
		need_rehash = 1;
	}
	spin_unlock(&dentry->d_lock);
	error = nfs_safe_remove(dentry);
	if (!error || error == -ENOENT) {
		nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
	} else if (need_rehash)
		d_rehash(dentry);
out:
	trace_nfs_unlink_exit(dir, dentry, error);
	return error;
}