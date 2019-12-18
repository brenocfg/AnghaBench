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
struct vfsmount {int dummy; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
struct nfs_clone_mount {int /*<<< orphan*/  authflavor; struct nfs_fattr* fattr; struct nfs_fh* fh; struct dentry* dentry; int /*<<< orphan*/  sb; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct vfsmount* ERR_CAST (char*) ; 
 struct vfsmount* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_USER ; 
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  NFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 char* nfs_devname (struct dentry*,char*,int /*<<< orphan*/ ) ; 
 struct vfsmount* nfs_do_clone_mount (int /*<<< orphan*/ ,char*,struct nfs_clone_mount*) ; 

struct vfsmount *nfs_do_submount(struct dentry *dentry, struct nfs_fh *fh,
				 struct nfs_fattr *fattr, rpc_authflavor_t authflavor)
{
	struct nfs_clone_mount mountdata = {
		.sb = dentry->d_sb,
		.dentry = dentry,
		.fh = fh,
		.fattr = fattr,
		.authflavor = authflavor,
	};
	struct vfsmount *mnt;
	char *page = (char *) __get_free_page(GFP_USER);
	char *devname;

	if (page == NULL)
		return ERR_PTR(-ENOMEM);

	devname = nfs_devname(dentry, page, PAGE_SIZE);
	if (IS_ERR(devname))
		mnt = ERR_CAST(devname);
	else
		mnt = nfs_do_clone_mount(NFS_SB(dentry->d_sb), devname, &mountdata);

	free_page((unsigned long)page);
	return mnt;
}