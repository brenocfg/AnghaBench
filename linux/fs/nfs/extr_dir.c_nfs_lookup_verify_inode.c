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
struct nfs_server {int caps; int flags; } ;
struct inode {int i_mode; scalar_t__ i_nlink; } ;

/* Variables and functions */
 int ECHILD ; 
 int ESTALE ; 
 scalar_t__ IS_AUTOMOUNT (struct inode*) ; 
 unsigned int LOOKUP_OPEN ; 
 unsigned int LOOKUP_RCU ; 
 unsigned int LOOKUP_REVAL ; 
 int NFS_CAP_ATOMIC_OPEN ; 
 int NFS_MOUNT_NOCTO ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
#define  S_IFDIR 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int __nfs_revalidate_inode (struct nfs_server*,struct inode*) ; 

__attribute__((used)) static
int nfs_lookup_verify_inode(struct inode *inode, unsigned int flags)
{
	struct nfs_server *server = NFS_SERVER(inode);
	int ret;

	if (IS_AUTOMOUNT(inode))
		return 0;

	if (flags & LOOKUP_OPEN) {
		switch (inode->i_mode & S_IFMT) {
		case S_IFREG:
			/* A NFSv4 OPEN will revalidate later */
			if (server->caps & NFS_CAP_ATOMIC_OPEN)
				goto out;
			/* Fallthrough */
		case S_IFDIR:
			if (server->flags & NFS_MOUNT_NOCTO)
				break;
			/* NFS close-to-open cache consistency validation */
			goto out_force;
		}
	}

	/* VFS wants an on-the-wire revalidation */
	if (flags & LOOKUP_REVAL)
		goto out_force;
out:
	return (inode->i_nlink == 0) ? -ESTALE : 0;
out_force:
	if (flags & LOOKUP_RCU)
		return -ECHILD;
	ret = __nfs_revalidate_inode(server, inode);
	if (ret != 0)
		return ret;
	goto out;
}