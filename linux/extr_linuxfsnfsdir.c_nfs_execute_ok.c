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
struct nfs_server {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int EACCES ; 
 int ECHILD ; 
 int MAY_NOT_BLOCK ; 
 int /*<<< orphan*/  NFS_INO_INVALID_OTHER ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int __nfs_revalidate_inode (struct nfs_server*,struct inode*) ; 
 int /*<<< orphan*/  execute_ok (struct inode*) ; 
 scalar_t__ nfs_check_cache_invalid (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_execute_ok(struct inode *inode, int mask)
{
	struct nfs_server *server = NFS_SERVER(inode);
	int ret = 0;

	if (S_ISDIR(inode->i_mode))
		return 0;
	if (nfs_check_cache_invalid(inode, NFS_INO_INVALID_OTHER)) {
		if (mask & MAY_NOT_BLOCK)
			return -ECHILD;
		ret = __nfs_revalidate_inode(server, inode);
	}
	if (ret == 0 && !execute_ok(inode))
		ret = -EACCES;
	return ret;
}