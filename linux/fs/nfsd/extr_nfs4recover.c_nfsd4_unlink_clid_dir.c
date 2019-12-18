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
struct nfsd_net {TYPE_2__* rec_file; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct TYPE_4__ {TYPE_1__ f_path; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  dprintk (char*,int,char*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int) ; 
 int vfs_rmdir (int /*<<< orphan*/ ,struct dentry*) ; 

__attribute__((used)) static int
nfsd4_unlink_clid_dir(char *name, int namlen, struct nfsd_net *nn)
{
	struct dentry *dir, *dentry;
	int status;

	dprintk("NFSD: nfsd4_unlink_clid_dir. name %.*s\n", namlen, name);

	dir = nn->rec_file->f_path.dentry;
	inode_lock_nested(d_inode(dir), I_MUTEX_PARENT);
	dentry = lookup_one_len(name, dir, namlen);
	if (IS_ERR(dentry)) {
		status = PTR_ERR(dentry);
		goto out_unlock;
	}
	status = -ENOENT;
	if (d_really_is_negative(dentry))
		goto out;
	status = vfs_rmdir(d_inode(dir), dentry);
out:
	dput(dentry);
out_unlock:
	inode_unlock(d_inode(dir));
	return status;
}