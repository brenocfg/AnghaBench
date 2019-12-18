#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct super_block {int dummy; } ;
struct path {int dummy; } ;
struct TYPE_7__ {int index; int metacopy; int nfs_export; } ;
struct ovl_fs {int tmpfile; int noxattr; TYPE_1__ config; scalar_t__ xino_bits; TYPE_2__* workdir; int /*<<< orphan*/  workdir_trap; struct vfsmount* upper_mnt; } ;
struct dentry {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int FILEID_INO32_GEN ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  OVL_WORKDIR_NAME ; 
 int /*<<< orphan*/  OVL_XATTR_OPAQUE ; 
 int S_IFREG ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mnt_drop_write (struct vfsmount*) ; 
 int mnt_want_write (struct vfsmount*) ; 
 int ovl_can_decode_fh (int /*<<< orphan*/ ) ; 
 int ovl_check_d_type_supported (struct path*) ; 
 int ovl_do_setxattr (TYPE_2__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct dentry* ovl_do_tmpfile (TYPE_2__*,int) ; 
 int ovl_setup_trap (struct super_block*,TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* ovl_workdir_create (struct ovl_fs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  vfs_removexattr (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_make_workdir(struct super_block *sb, struct ovl_fs *ofs,
			    struct path *workpath)
{
	struct vfsmount *mnt = ofs->upper_mnt;
	struct dentry *temp;
	int fh_type;
	int err;

	err = mnt_want_write(mnt);
	if (err)
		return err;

	ofs->workdir = ovl_workdir_create(ofs, OVL_WORKDIR_NAME, false);
	if (!ofs->workdir)
		goto out;

	err = ovl_setup_trap(sb, ofs->workdir, &ofs->workdir_trap, "workdir");
	if (err)
		goto out;

	/*
	 * Upper should support d_type, else whiteouts are visible.  Given
	 * workdir and upper are on same fs, we can do iterate_dir() on
	 * workdir. This check requires successful creation of workdir in
	 * previous step.
	 */
	err = ovl_check_d_type_supported(workpath);
	if (err < 0)
		goto out;

	/*
	 * We allowed this configuration and don't want to break users over
	 * kernel upgrade. So warn instead of erroring out.
	 */
	if (!err)
		pr_warn("overlayfs: upper fs needs to support d_type.\n");

	/* Check if upper/work fs supports O_TMPFILE */
	temp = ovl_do_tmpfile(ofs->workdir, S_IFREG | 0);
	ofs->tmpfile = !IS_ERR(temp);
	if (ofs->tmpfile)
		dput(temp);
	else
		pr_warn("overlayfs: upper fs does not support tmpfile.\n");

	/*
	 * Check if upper/work fs supports trusted.overlay.* xattr
	 */
	err = ovl_do_setxattr(ofs->workdir, OVL_XATTR_OPAQUE, "0", 1, 0);
	if (err) {
		ofs->noxattr = true;
		ofs->config.index = false;
		ofs->config.metacopy = false;
		pr_warn("overlayfs: upper fs does not support xattr, falling back to index=off and metacopy=off.\n");
		err = 0;
	} else {
		vfs_removexattr(ofs->workdir, OVL_XATTR_OPAQUE);
	}

	/* Check if upper/work fs supports file handles */
	fh_type = ovl_can_decode_fh(ofs->workdir->d_sb);
	if (ofs->config.index && !fh_type) {
		ofs->config.index = false;
		pr_warn("overlayfs: upper fs does not support file handles, falling back to index=off.\n");
	}

	/* Check if upper fs has 32bit inode numbers */
	if (fh_type != FILEID_INO32_GEN)
		ofs->xino_bits = 0;

	/* NFS export of r/w mount depends on index */
	if (ofs->config.nfs_export && !ofs->config.index) {
		pr_warn("overlayfs: NFS export requires \"index=on\", falling back to nfs_export=off.\n");
		ofs->config.nfs_export = false;
	}
out:
	mnt_drop_write(mnt);
	return err;
}