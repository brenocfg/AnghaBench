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
struct inode {int dummy; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_INO_REVAL_PAGECACHE ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int O_DIRECT ; 
 int __nfs_revalidate_inode (struct nfs_server*,struct inode*) ; 
 scalar_t__ nfs_check_cache_invalid (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_revalidate_file_size(struct inode *inode, struct file *filp)
{
	struct nfs_server *server = NFS_SERVER(inode);

	if (filp->f_flags & O_DIRECT)
		goto force_reval;
	if (nfs_check_cache_invalid(inode, NFS_INO_REVAL_PAGECACHE))
		goto force_reval;
	return 0;
force_reval:
	return __nfs_revalidate_inode(server, inode);
}