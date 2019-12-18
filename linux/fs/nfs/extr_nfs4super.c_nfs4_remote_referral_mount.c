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
struct nfs_mount_info {void* cloned; int /*<<< orphan*/ * mntfh; int /*<<< orphan*/  set_security; int /*<<< orphan*/  fill_super; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_CAST (struct nfs_server*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct nfs_server*) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 struct nfs_server* nfs4_create_referral_server (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nfs_alloc_fhandle () ; 
 int /*<<< orphan*/  nfs_clone_sb_security ; 
 int /*<<< orphan*/  nfs_fill_super ; 
 int /*<<< orphan*/  nfs_free_fhandle (int /*<<< orphan*/ *) ; 
 struct dentry* nfs_fs_mount_common (struct nfs_server*,int,char const*,struct nfs_mount_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_v4 ; 

__attribute__((used)) static struct dentry *
nfs4_remote_referral_mount(struct file_system_type *fs_type, int flags,
			   const char *dev_name, void *raw_data)
{
	struct nfs_mount_info mount_info = {
		.fill_super = nfs_fill_super,
		.set_security = nfs_clone_sb_security,
		.cloned = raw_data,
	};
	struct nfs_server *server;
	struct dentry *mntroot = ERR_PTR(-ENOMEM);

	dprintk("--> nfs4_referral_get_sb()\n");

	mount_info.mntfh = nfs_alloc_fhandle();
	if (mount_info.cloned == NULL || mount_info.mntfh == NULL)
		goto out;

	/* create a new volume representation */
	server = nfs4_create_referral_server(mount_info.cloned, mount_info.mntfh);
	if (IS_ERR(server)) {
		mntroot = ERR_CAST(server);
		goto out;
	}

	mntroot = nfs_fs_mount_common(server, flags, dev_name, &mount_info, &nfs_v4);
out:
	nfs_free_fhandle(mount_info.mntfh);
	return mntroot;
}