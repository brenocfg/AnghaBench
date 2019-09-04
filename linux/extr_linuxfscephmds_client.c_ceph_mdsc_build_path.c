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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {struct dentry* d_parent; int /*<<< orphan*/  d_lock; TYPE_1__ d_name; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 scalar_t__ CEPH_SNAPDIR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  ceph_ino (struct inode*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  d_count (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rename_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 

char *ceph_mdsc_build_path(struct dentry *dentry, int *plen, u64 *base,
			   int stop_on_nosnap)
{
	struct dentry *temp;
	char *path;
	int len, pos;
	unsigned seq;

	if (!dentry)
		return ERR_PTR(-EINVAL);

retry:
	len = 0;
	seq = read_seqbegin(&rename_lock);
	rcu_read_lock();
	for (temp = dentry; !IS_ROOT(temp);) {
		struct inode *inode = d_inode(temp);
		if (inode && ceph_snap(inode) == CEPH_SNAPDIR)
			len++;  /* slash only */
		else if (stop_on_nosnap && inode &&
			 ceph_snap(inode) == CEPH_NOSNAP)
			break;
		else
			len += 1 + temp->d_name.len;
		temp = temp->d_parent;
	}
	rcu_read_unlock();
	if (len)
		len--;  /* no leading '/' */

	path = kmalloc(len+1, GFP_NOFS);
	if (!path)
		return ERR_PTR(-ENOMEM);
	pos = len;
	path[pos] = 0;	/* trailing null */
	rcu_read_lock();
	for (temp = dentry; !IS_ROOT(temp) && pos != 0; ) {
		struct inode *inode;

		spin_lock(&temp->d_lock);
		inode = d_inode(temp);
		if (inode && ceph_snap(inode) == CEPH_SNAPDIR) {
			dout("build_path path+%d: %p SNAPDIR\n",
			     pos, temp);
		} else if (stop_on_nosnap && inode &&
			   ceph_snap(inode) == CEPH_NOSNAP) {
			spin_unlock(&temp->d_lock);
			break;
		} else {
			pos -= temp->d_name.len;
			if (pos < 0) {
				spin_unlock(&temp->d_lock);
				break;
			}
			strncpy(path + pos, temp->d_name.name,
				temp->d_name.len);
		}
		spin_unlock(&temp->d_lock);
		if (pos)
			path[--pos] = '/';
		temp = temp->d_parent;
	}
	rcu_read_unlock();
	if (pos != 0 || read_seqretry(&rename_lock, seq)) {
		pr_err("build_path did not end path lookup where "
		       "expected, namelen is %d, pos is %d\n", len, pos);
		/* presumably this is only possible if racing with a
		   rename of one of the parent directories (we can not
		   lock the dentries above us to prevent this, but
		   retrying should be harmless) */
		kfree(path);
		goto retry;
	}

	*base = ceph_ino(d_inode(temp));
	*plen = len;
	dout("build_path on %p %d built %llx '%.*s'\n",
	     dentry, d_count(dentry), *base, len, path);
	return path;
}