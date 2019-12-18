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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;
struct ceph_nfs_snapfh {scalar_t__ snapid; void* ino; scalar_t__ hash; void* parent_ino; } ;

/* Variables and functions */
 scalar_t__ CEPH_SNAPDIR ; 
 int EINVAL ; 
 int FILEID_BTRFS_WITH_PARENT ; 
 int FILEID_INVALID ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_dentry_hash (struct inode*,struct dentry*) ; 
 void* ceph_ino (struct inode*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  ceph_vinop (struct inode*) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 struct inode* d_inode_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int ceph_encode_snapfh(struct inode *inode, u32 *rawfh, int *max_len,
			      struct inode *parent_inode)
{
	static const int snap_handle_length =
		sizeof(struct ceph_nfs_snapfh) >> 2;
	struct ceph_nfs_snapfh *sfh = (void *)rawfh;
	u64 snapid = ceph_snap(inode);
	int ret;
	bool no_parent = true;

	if (*max_len < snap_handle_length) {
		*max_len = snap_handle_length;
		ret = FILEID_INVALID;
		goto out;
	}

	ret =  -EINVAL;
	if (snapid != CEPH_SNAPDIR) {
		struct inode *dir;
		struct dentry *dentry = d_find_alias(inode);
		if (!dentry)
			goto out;

		rcu_read_lock();
		dir = d_inode_rcu(dentry->d_parent);
		if (ceph_snap(dir) != CEPH_SNAPDIR) {
			sfh->parent_ino = ceph_ino(dir);
			sfh->hash = ceph_dentry_hash(dir, dentry);
			no_parent = false;
		}
		rcu_read_unlock();
		dput(dentry);
	}

	if (no_parent) {
		if (!S_ISDIR(inode->i_mode))
			goto out;
		sfh->parent_ino = sfh->ino;
		sfh->hash = 0;
	}
	sfh->ino = ceph_ino(inode);
	sfh->snapid = snapid;

	*max_len = snap_handle_length;
	ret = FILEID_BTRFS_WITH_PARENT;
out:
	dout("encode_snapfh %llx.%llx ret=%d\n", ceph_vinop(inode), ret);
	return ret;
}