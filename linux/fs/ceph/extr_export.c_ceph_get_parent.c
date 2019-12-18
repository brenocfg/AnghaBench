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
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 scalar_t__ CEPH_SNAPDIR ; 
 int /*<<< orphan*/  EINVAL ; 
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ PTR_ERR_OR_ZERO (struct dentry*) ; 
 struct dentry* __get_parent (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 struct inode* __lookup_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* ceph_get_snapdir (struct inode*) ; 
 int /*<<< orphan*/  ceph_ino (struct inode*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  ceph_vinop (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 struct dentry* d_obtain_root (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static struct dentry *ceph_get_parent(struct dentry *child)
{
	struct inode *inode = d_inode(child);
	struct dentry *dn;

	if (ceph_snap(inode) != CEPH_NOSNAP) {
		struct inode* dir;
		bool unlinked = false;
		/* do not support non-directory */
		if (!d_is_dir(child)) {
			dn = ERR_PTR(-EINVAL);
			goto out;
		}
		dir = __lookup_inode(inode->i_sb, ceph_ino(inode));
		if (IS_ERR(dir)) {
			dn = ERR_CAST(dir);
			goto out;
		}
		/* There can be multiple paths to access snapped inode.
		 * For simplicity, treat snapdir of head inode as parent */
		if (ceph_snap(inode) != CEPH_SNAPDIR) {
			struct inode *snapdir = ceph_get_snapdir(dir);
			if (dir->i_nlink == 0)
				unlinked = true;
			iput(dir);
			if (IS_ERR(snapdir)) {
				dn = ERR_CAST(snapdir);
				goto out;
			}
			dir = snapdir;
		}
		/* If directory has already been deleted, futher get_parent
		 * will fail. Do not mark snapdir dentry as disconnected,
		 * this prevent exportfs from doing futher get_parent. */
		if (unlinked)
			dn = d_obtain_root(dir);
		else
			dn = d_obtain_alias(dir);
	} else {
		dn = __get_parent(child->d_sb, child, 0);
	}
out:
	dout("get_parent %p ino %llx.%llx err=%ld\n",
	     child, ceph_vinop(inode), (long)PTR_ERR_OR_ZERO(dn));
	return dn;
}