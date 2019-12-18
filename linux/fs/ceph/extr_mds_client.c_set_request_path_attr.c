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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int build_dentry_path (struct dentry*,struct inode*,char const**,int*,scalar_t__*,int*,int) ; 
 int build_inode_path (struct inode*,char const**,int*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  ceph_ino (struct inode*) ; 
 int /*<<< orphan*/  ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,int,char const*,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int set_request_path_attr(struct inode *rinode, struct dentry *rdentry,
				  struct inode *rdiri, const char *rpath,
				  u64 rino, const char **ppath, int *pathlen,
				  u64 *ino, bool *freepath, bool parent_locked)
{
	int r = 0;

	if (rinode) {
		r = build_inode_path(rinode, ppath, pathlen, ino, freepath);
		dout(" inode %p %llx.%llx\n", rinode, ceph_ino(rinode),
		     ceph_snap(rinode));
	} else if (rdentry) {
		r = build_dentry_path(rdentry, rdiri, ppath, pathlen, ino,
					freepath, parent_locked);
		dout(" dentry %p %llx/%.*s\n", rdentry, *ino, *pathlen,
		     *ppath);
	} else if (rpath || rino) {
		*ino = rino;
		*ppath = rpath;
		*pathlen = rpath ? strlen(rpath) : 0;
		dout(" path %.*s\n", *pathlen, rpath);
	}

	return r;
}