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
typedef  int /*<<< orphan*/  u32 ;
struct path {int /*<<< orphan*/  dentry; } ;
struct kstat {int dummy; } ;
struct inode {int dummy; } ;
struct fuse_conn {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_allow_current_process (struct fuse_conn*) ; 
 int fuse_update_get_attr (struct inode*,int /*<<< orphan*/ *,struct kstat*,int /*<<< orphan*/ ,unsigned int) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 

__attribute__((used)) static int fuse_getattr(const struct path *path, struct kstat *stat,
			u32 request_mask, unsigned int flags)
{
	struct inode *inode = d_inode(path->dentry);
	struct fuse_conn *fc = get_fuse_conn(inode);

	if (!fuse_allow_current_process(fc))
		return -EACCES;

	return fuse_update_get_attr(inode, NULL, stat, request_mask, flags);
}