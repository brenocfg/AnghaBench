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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 int /*<<< orphan*/  ceph_ino (struct inode*) ; 
 char* ceph_mdsc_build_path (struct dentry*,int*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

__attribute__((used)) static int build_inode_path(struct inode *inode,
			    const char **ppath, int *ppathlen, u64 *pino,
			    bool *pfreepath)
{
	struct dentry *dentry;
	char *path;

	if (ceph_snap(inode) == CEPH_NOSNAP) {
		*pino = ceph_ino(inode);
		*ppathlen = 0;
		return 0;
	}
	dentry = d_find_alias(inode);
	path = ceph_mdsc_build_path(dentry, ppathlen, pino, 1);
	dput(dentry);
	if (IS_ERR(path))
		return PTR_ERR(path);
	*ppath = path;
	*pfreepath = true;
	return 0;
}