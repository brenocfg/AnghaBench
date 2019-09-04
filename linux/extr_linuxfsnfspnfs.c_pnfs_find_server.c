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
struct nfs_open_context {int /*<<< orphan*/  dentry; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 struct dentry* dget_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

__attribute__((used)) static struct nfs_server *
pnfs_find_server(struct inode *inode, struct nfs_open_context *ctx)
{
	struct nfs_server *server;

	if (inode) {
		server = NFS_SERVER(inode);
	} else {
		struct dentry *parent_dir = dget_parent(ctx->dentry);
		server = NFS_SERVER(parent_dir->d_inode);
		dput(parent_dir);
	}
	return server;
}