#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct nfs_inode {TYPE_4__ vfs_inode; TYPE_3__ fh; int /*<<< orphan*/ * fscache; } ;
struct nfs_fscache_inode_auxdata {int /*<<< orphan*/  change_attr; void* ctime; void* mtime; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  auxdata ;
struct TYPE_13__ {int /*<<< orphan*/  fscache; } ;
struct TYPE_12__ {TYPE_2__* nfs_client; } ;
struct TYPE_9__ {TYPE_1__* rpc_ops; } ;
struct TYPE_8__ {int version; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 TYPE_7__* NFS_SB (int /*<<< orphan*/ ) ; 
 TYPE_5__* NFS_SERVER (TYPE_4__*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfs_fscache_inode_auxdata*,int,struct nfs_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inode_peek_iversion_raw (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (struct nfs_fscache_inode_auxdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_fscache_inode_object_def ; 
 void* timespec64_to_timespec (int /*<<< orphan*/ ) ; 

void nfs_fscache_init_inode(struct inode *inode)
{
	struct nfs_fscache_inode_auxdata auxdata;
	struct nfs_inode *nfsi = NFS_I(inode);

	nfsi->fscache = NULL;
	if (!S_ISREG(inode->i_mode))
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