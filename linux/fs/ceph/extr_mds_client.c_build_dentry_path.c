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
struct TYPE_2__ {char* name; int len; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 int /*<<< orphan*/  ceph_ino (struct inode*) ; 
 char* ceph_mdsc_build_path (struct dentry*,int*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 struct inode* d_inode_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int build_dentry_path(struct dentry *dentry, struct inode *dir,
			     const char **ppath, int *ppathlen, u64 *pino,
			     bool *pfreepath, bool parent_locked)
{
	char *path;

	rcu_read_lock();
	if (!dir)
		dir = d_inode_rcu(dentry->d_parent);
	if (dir && parent_locked && ceph_snap(dir) == CEPH_NOSNAP) {
		*pino = ceph_ino(dir);
		rcu_read_unlock();
		*ppath = dentry->d_name.name;
		*ppathlen = dentry->d_name.len;
		return 0;
	}
	rcu_read_unlock();
	path = ceph_mdsc_build_path(dentry, ppathlen, pino, 1);
	if (IS_ERR(path))
		return PTR_ERR(path);
	*ppath = path;
	*pfreepath = true;
	return 0;
}