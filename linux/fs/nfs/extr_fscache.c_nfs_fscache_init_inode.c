#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {TYPE_2__* nfs_client; scalar_t__ fscache; } ;
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct nfs_inode {struct inode vfs_inode; TYPE_3__ fh; int /*<<< orphan*/ * fscache; } ;
struct nfs_fscache_inode_auxdata {int /*<<< orphan*/  change_attr; void* ctime; void* mtime; } ;
typedef  int /*<<< orphan*/  auxdata ;
struct TYPE_8__ {int /*<<< orphan*/  fscache; } ;
struct TYPE_6__ {TYPE_1__* rpc_ops; } ;
struct TYPE_5__ {int version; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 TYPE_4__* NFS_SB (int /*<<< orphan*/ ) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfs_fscache_inode_auxdata*,int,struct nfs_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inode_peek_iversion_raw (struct inode*) ; 
 int /*<<< orphan*/  memset (struct nfs_fscache_inode_auxdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_fscache_inode_object_def ; 
 void* timespec64_to_timespec (int /*<<< orphan*/ ) ; 

void nfs_fscache_init_inode(struct inode *inode)
{
	struct nfs_fscache_inode_auxdata auxdata;
	struct nfs_server *nfss = NFS_SERVER(inode);
	struct nfs_inode *nfsi = NFS_I(inode);

	nfsi->fscache = NULL;
	if (!(nfss->fscache && S_ISREG(inode->i_mode)))
		return;

	memset(&auxdata, 0, sizeof(auxdata));
	auxdata.mtime = timespec64_to_timespec(nfsi->vfs_inode.i_mtime);
	auxdata.ctime = timespec64_to_timespec(nfsi->vfs_inode.i_ctime);

	if (NFS_SERVER(&nfsi->vfs_inode)->nfs_client->rpc_ops->version == 4)
		auxdata.change_attr = inode_peek_iversion_raw(&nfsi->vfs_inode);

	nfsi->fscache = fscache_acquire_cookie(NFS_SB(inode->i_sb)->fscache,
					       &nfs_fscache_inode_object_def,
					       nfsi->fh.data, nfsi->fh.size,
					       &auxdata, sizeof(auxdata),
					       nfsi, nfsi->vfs_inode.i_size, false);
}