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
struct super_block {int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_iflags; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_bdi; struct nfs_server* s_fs_info; } ;
struct nfs_subversion {int /*<<< orphan*/  nfs_fs; } ;
struct nfs_server {int flags; struct super_block* super; int /*<<< orphan*/  rpages; int /*<<< orphan*/  s_dev; } ;
struct nfs_sb_mountdata {int mntflags; struct nfs_server* server; } ;
struct nfs_mount_info {int (* set_security ) (struct super_block*,struct super_block*,struct nfs_mount_info*) ;int /*<<< orphan*/  mntfh; TYPE_2__* cloned; int /*<<< orphan*/  parsed; int /*<<< orphan*/  (* fill_super ) (struct super_block*,struct nfs_mount_info*) ;} ;
struct dentry {int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_iflags; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_bdi; struct nfs_server* s_fs_info; } ;
struct TYPE_4__ {TYPE_1__* sb; } ;
struct TYPE_3__ {int s_flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct super_block* ERR_CAST (struct super_block*) ; 
 struct super_block* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int NFS_MOUNT_NOAC ; 
 int NFS_MOUNT_UNSHARED ; 
 int /*<<< orphan*/  SB_ACTIVE ; 
 int /*<<< orphan*/  SB_I_MULTIROOT ; 
 int SB_SYNCHRONOUS ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  dput (struct super_block*) ; 
 int nfs_compare_super (struct super_block*,void*) ; 
 int /*<<< orphan*/  nfs_free_server (struct nfs_server*) ; 
 int /*<<< orphan*/  nfs_get_cache_cookie (struct super_block*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct super_block* nfs_get_root (struct super_block*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  nfs_set_readahead (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_set_super ; 
 struct super_block* sget (int /*<<< orphan*/ ,int (*) (struct super_block*,void*),int /*<<< orphan*/ ,int,struct nfs_sb_mountdata*) ; 
 int /*<<< orphan*/  stub1 (struct super_block*,struct nfs_mount_info*) ; 
 int stub2 (struct super_block*,struct super_block*,struct nfs_mount_info*) ; 
 int super_setup_bdi_name (struct super_block*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct dentry *nfs_fs_mount_common(struct nfs_server *server,
				   int flags, const char *dev_name,
				   struct nfs_mount_info *mount_info,
				   struct nfs_subversion *nfs_mod)
{
	struct super_block *s;
	struct dentry *mntroot = ERR_PTR(-ENOMEM);
	int (*compare_super)(struct super_block *, void *) = nfs_compare_super;
	struct nfs_sb_mountdata sb_mntdata = {
		.mntflags = flags,
		.server = server,
	};
	int error;

	if (server->flags & NFS_MOUNT_UNSHARED)
		compare_super = NULL;

	/* -o noac implies -o sync */
	if (server->flags & NFS_MOUNT_NOAC)
		sb_mntdata.mntflags |= SB_SYNCHRONOUS;

	if (mount_info->cloned != NULL && mount_info->cloned->sb != NULL)
		if (mount_info->cloned->sb->s_flags & SB_SYNCHRONOUS)
			sb_mntdata.mntflags |= SB_SYNCHRONOUS;

	/* Get a superblock - note that we may end up sharing one that already exists */
	s = sget(nfs_mod->nfs_fs, compare_super, nfs_set_super, flags, &sb_mntdata);
	if (IS_ERR(s)) {
		mntroot = ERR_CAST(s);
		goto out_err_nosb;
	}

	if (s->s_fs_info != server) {
		nfs_free_server(server);
		server = NULL;
	} else {
		error = super_setup_bdi_name(s, "%u:%u", MAJOR(server->s_dev),
					     MINOR(server->s_dev));
		if (error) {
			mntroot = ERR_PTR(error);
			goto error_splat_super;
		}
		nfs_set_readahead(s->s_bdi, server->rpages);
		server->super = s;
	}

	if (!s->s_root) {
		/* initial superblock/root creation */
		mount_info->fill_super(s, mount_info);
		nfs_get_cache_cookie(s, mount_info->parsed, mount_info->cloned);
		if (!(server->flags & NFS_MOUNT_UNSHARED))
			s->s_iflags |= SB_I_MULTIROOT;
	}

	mntroot = nfs_get_root(s, mount_info->mntfh, dev_name);
	if (IS_ERR(mntroot))
		goto error_splat_super;

	error = mount_info->set_security(s, mntroot, mount_info);
	if (error)
		goto error_splat_root;

	s->s_flags |= SB_ACTIVE;

out:
	return mntroot;

out_err_nosb:
	nfs_free_server(server);
	goto out;

error_splat_root:
	dput(mntroot);
	mntroot = ERR_PTR(error);
error_splat_super:
	deactivate_locked_super(s);
	goto out;
}