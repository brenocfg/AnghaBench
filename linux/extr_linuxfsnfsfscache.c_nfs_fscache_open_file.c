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
struct TYPE_2__ {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct nfs_inode {int /*<<< orphan*/  flags; TYPE_1__ vfs_inode; } ;
struct nfs_fscache_inode_auxdata {void* ctime; void* mtime; } ;
struct inode {int dummy; } ;
struct fscache_cookie {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  auxdata ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_FSCACHE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct nfs_inode*) ; 
 scalar_t__ fscache_cookie_enabled (struct fscache_cookie*) ; 
 int /*<<< orphan*/  fscache_cookie_valid (struct fscache_cookie*) ; 
 int /*<<< orphan*/  fscache_disable_cookie (struct fscache_cookie*,struct nfs_fscache_inode_auxdata*,int) ; 
 int /*<<< orphan*/  fscache_enable_cookie (struct fscache_cookie*,struct nfs_fscache_inode_auxdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  fscache_uncache_all_inode_pages (struct fscache_cookie*,struct inode*) ; 
 scalar_t__ inode_is_open_for_write (struct inode*) ; 
 int /*<<< orphan*/  memset (struct nfs_fscache_inode_auxdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_fscache_can_enable ; 
 struct fscache_cookie* nfs_i_fscache (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* timespec64_to_timespec (int /*<<< orphan*/ ) ; 

void nfs_fscache_open_file(struct inode *inode, struct file *filp)
{
	struct nfs_fscache_inode_auxdata auxdata;
	struct nfs_inode *nfsi = NFS_I(inode);
	struct fscache_cookie *cookie = nfs_i_fscache(inode);

	if (!fscache_cookie_valid(cookie))
		return;

	memset(&auxdata, 0, sizeof(auxdata));
	auxdata.mtime = timespec64_to_timespec(nfsi->vfs_inode.i_mtime);
	auxdata.ctime = timespec64_to_timespec(nfsi->vfs_inode.i_ctime);

	if (inode_is_open_for_write(inode)) {
		dfprintk(FSCACHE, "NFS: nfsi 0x%p disabling cache\n", nfsi);
		clear_bit(NFS_INO_FSCACHE, &nfsi->flags);
		fscache_disable_cookie(cookie, &auxdata, true);
		fscache_uncache_all_inode_pages(cookie, inode);
	} else {
		dfprintk(FSCACHE, "NFS: nfsi 0x%p enabling cache\n", nfsi);
		fscache_enable_cookie(cookie, &auxdata, nfsi->vfs_inode.i_size,
				      nfs_fscache_can_enable, inode);
		if (fscache_cookie_enabled(cookie))
			set_bit(NFS_INO_FSCACHE, &NFS_I(inode)->flags);
	}
}