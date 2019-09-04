#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct nfs_inode {int /*<<< orphan*/ * fscache; TYPE_1__ vfs_inode; } ;
struct nfs_fscache_inode_auxdata {void* ctime; void* mtime; } ;
struct inode {int dummy; } ;
struct fscache_cookie {int dummy; } ;
typedef  int /*<<< orphan*/  auxdata ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct nfs_inode*,struct fscache_cookie*) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (struct fscache_cookie*,struct nfs_fscache_inode_auxdata*,int) ; 
 int /*<<< orphan*/  memset (struct nfs_fscache_inode_auxdata*,int /*<<< orphan*/ ,int) ; 
 struct fscache_cookie* nfs_i_fscache (struct inode*) ; 
 void* timespec64_to_timespec (int /*<<< orphan*/ ) ; 

void nfs_fscache_clear_inode(struct inode *inode)
{
	struct nfs_fscache_inode_auxdata auxdata;
	struct nfs_inode *nfsi = NFS_I(inode);
	struct fscache_cookie *cookie = nfs_i_fscache(inode);

	dfprintk(FSCACHE, "NFS: clear cookie (0x%p/0x%p)\n", nfsi, cookie);

	memset(&auxdata, 0, sizeof(auxdata));
	auxdata.mtime = timespec64_to_timespec(nfsi->vfs_inode.i_mtime);
	auxdata.ctime = timespec64_to_timespec(nfsi->vfs_inode.i_ctime);
	fscache_relinquish_cookie(cookie, &auxdata, false);
	nfsi->fscache = NULL;
}