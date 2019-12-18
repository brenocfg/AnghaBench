#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {int flags; } ;
struct nfs_open_context {int mode; int /*<<< orphan*/  dentry; } ;
struct nfs_inode {int cache_validity; int /*<<< orphan*/  open_files; } ;
struct inode {TYPE_1__* i_mapping; } ;
struct TYPE_4__ {scalar_t__ (* have_delegation ) (struct inode*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ nrpages; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_READ ; 
 int FMODE_WRITE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_DATA ; 
 int NFS_MOUNT_NOCTO ; 
 TYPE_2__* NFS_PROTO (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_revalidate_inode (struct nfs_server*,struct inode*) ; 
 scalar_t__ stub1 (struct inode*,int /*<<< orphan*/ ) ; 

void nfs_close_context(struct nfs_open_context *ctx, int is_sync)
{
	struct nfs_inode *nfsi;
	struct inode *inode;
	struct nfs_server *server;

	if (!(ctx->mode & FMODE_WRITE))
		return;
	if (!is_sync)
		return;
	inode = d_inode(ctx->dentry);
	if (NFS_PROTO(inode)->have_delegation(inode, FMODE_READ))
		return;
	nfsi = NFS_I(inode);
	if (inode->i_mapping->nrpages == 0)
		return;
	if (nfsi->cache_validity & NFS_INO_INVALID_DATA)
		return;
	if (!list_empty(&nfsi->open_files))
		return;
	server = NFS_SERVER(inode);
	if (server->flags & NFS_MOUNT_NOCTO)
		return;
	nfs_revalidate_inode(server, inode);
}