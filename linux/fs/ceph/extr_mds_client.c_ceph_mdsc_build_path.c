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
struct dentry {int /*<<< orphan*/  d_parent; int /*<<< orphan*/  d_lock; TYPE_1__ d_name; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 scalar_t__ CEPH_SNAPDIR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ROOT (struct dentry*) ; 
 int PATH_MAX ; 
 struct dentry* READ_ONCE (int /*<<< orphan*/ ) ; 
 char* __getname () ; 
 int /*<<< orphan*/  ceph_ino (struct inode*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  d_count (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rename_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

char *ceph_mdsc_build_path(struct dentry *dentry, int *plen, u64 *pbase,
			   int stop_on_nosnap)
{
	struct dentry *temp;
	char *path;
	int pos;
	unsigned seq;
	u64 base;

	if (!dentry)
		return ERR_PTR(-EINVAL);

	path = __getname();
	if (!path)
		return ERR_PTR(-ENOMEM);
retry:
	pos = PATH_MAX - 1;
	path[pos] = '\0';

	seq = read_seqbegin(&rename_lock);
	rcu_read_lock();
	temp = dentry;
	for (;;) {
		struct inode *inode;

		spin_lock(&temp->d_lock);
		inode = d_inode(temp);
		if (inode && ceph_snap(inode) == CEPH_SNAPDIR) {
			dout("build_path path+%d: %p SNAPDIR\n",
			     pos, temp);
		} else if (stop_on_nosnap && inode && dentry != temp &&
			   ceph_snap(inode) == CEPH_NOSNAP) {
			spin_unlock(&temp->d_lock);
			pos++; /* get rid of any prepended '/' */
			break;
		} else {
			pos -= temp->d_name.len;
			if (pos < 0) {
				spin_unlock(&temp->d_lock);
				break;
			}
			memcpy(path + pos, temp->d_name.name, temp->d_name.len);
		}
		spin_unlock(&temp->d_lock);
		temp = READ_ONCE(temp->d_parent);

		/* Are we at the root? */
		if (IS_ROOT(temp))
			break;

		/* Are we out of buffer? */
		if (--pos < 0)
			break;

		path[pos] = '/';
	}
	base = ceph_ino(d_inode(temp));
	rcu_read_unlock();
	if (pos < 0 || read_seqretry(&rename_lock, seq)) {
		pr_err("build_path did not end path lookup where "
		       "expected, pos is %d\n", pos);
		/* presumably this is only possible if racing with a
		   rename of one of the parent directories (we can not
		   lock the dentries above us to prevent this, but
		   retrying should be harmless) */
		goto retry;
	}

	*pbase = base;
	*plen = PATH_MAX - 1 - pos;
	dout("build_path on %p %d built %llx '%.*s'\n",
	     dentry, d_count(dentry), base, *plen, path + pos);
	return path + pos;
}