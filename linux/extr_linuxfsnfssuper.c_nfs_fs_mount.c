#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfs_subversion {TYPE_1__* rpc_ops; } ;
struct nfs_mount_info {int /*<<< orphan*/ * mntfh; TYPE_2__* parsed; int /*<<< orphan*/  set_security; int /*<<< orphan*/  fill_super; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  version; } ;
struct TYPE_6__ {struct dentry* (* try_mount ) (int,char const*,struct nfs_mount_info*,struct nfs_subversion*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 struct dentry* ERR_CAST (struct nfs_subversion*) ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct nfs_subversion*) ; 
 int NFS_TEXT_DATA ; 
 struct nfs_subversion* get_nfs_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs_alloc_fhandle () ; 
 TYPE_2__* nfs_alloc_parsed_mount_data () ; 
 int /*<<< orphan*/  nfs_fill_super ; 
 int /*<<< orphan*/  nfs_free_fhandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_free_parsed_mount_data (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_set_sb_security ; 
 int nfs_validate_mount_data (struct file_system_type*,void*,TYPE_2__*,int /*<<< orphan*/ *,char const*) ; 
 int nfs_validate_text_mount_data (void*,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  put_nfs_version (struct nfs_subversion*) ; 
 struct dentry* stub1 (int,char const*,struct nfs_mount_info*,struct nfs_subversion*) ; 

struct dentry *nfs_fs_mount(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *raw_data)
{
	struct nfs_mount_info mount_info = {
		.fill_super = nfs_fill_super,
		.set_security = nfs_set_sb_security,
	};
	struct dentry *mntroot = ERR_PTR(-ENOMEM);
	struct nfs_subversion *nfs_mod;
	int error;

	mount_info.parsed = nfs_alloc_parsed_mount_data();
	mount_info.mntfh = nfs_alloc_fhandle();
	if (mount_info.parsed == NULL || mount_info.mntfh == NULL)
		goto out;

	/* Validate the mount data */
	error = nfs_validate_mount_data(fs_type, raw_data, mount_info.parsed, mount_info.mntfh, dev_name);
	if (error == NFS_TEXT_DATA)
		error = nfs_validate_text_mount_data(raw_data, mount_info.parsed, dev_name);
	if (error < 0) {
		mntroot = ERR_PTR(error);
		goto out;
	}

	nfs_mod = get_nfs_version(mount_info.parsed->version);
	if (IS_ERR(nfs_mod)) {
		mntroot = ERR_CAST(nfs_mod);
		goto out;
	}

	mntroot = nfs_mod->rpc_ops->try_mount(flags, dev_name, &mount_info, nfs_mod);

	put_nfs_version(nfs_mod);
out:
	nfs_free_parsed_mount_data(mount_info.parsed);
	nfs_free_fhandle(mount_info.mntfh);
	return mntroot;
}