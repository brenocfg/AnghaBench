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
struct vfsmount {int dummy; } ;
struct super_block {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; } ;
struct ovl_fs {scalar_t__ indexdir; int /*<<< orphan*/  indexdir_trap; struct vfsmount* upper_mnt; } ;
struct ovl_entry {TYPE_1__* lowerstack; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVL_INDEXDIR_NAME ; 
 int /*<<< orphan*/  OVL_XATTR_ORIGIN ; 
 int /*<<< orphan*/  mnt_drop_write (struct vfsmount*) ; 
 int mnt_want_write (struct vfsmount*) ; 
 scalar_t__ ovl_check_origin_xattr (scalar_t__) ; 
 int ovl_indexdir_cleanup (struct ovl_fs*) ; 
 int ovl_setup_trap (struct super_block*,scalar_t__,int /*<<< orphan*/ *,char*) ; 
 int ovl_verify_origin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ovl_verify_set_fh (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int ovl_verify_upper (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ovl_workdir_create (struct ovl_fs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int ovl_get_indexdir(struct super_block *sb, struct ovl_fs *ofs,
			    struct ovl_entry *oe, struct path *upperpath)
{
	struct vfsmount *mnt = ofs->upper_mnt;
	int err;

	err = mnt_want_write(mnt);
	if (err)
		return err;

	/* Verify lower root is upper root origin */
	err = ovl_verify_origin(upperpath->dentry, oe->lowerstack[0].dentry,
				true);
	if (err) {
		pr_err("overlayfs: failed to verify upper root origin\n");
		goto out;
	}

	ofs->indexdir = ovl_workdir_create(ofs, OVL_INDEXDIR_NAME, true);
	if (ofs->indexdir) {
		err = ovl_setup_trap(sb, ofs->indexdir, &ofs->indexdir_trap,
				     "indexdir");
		if (err)
			goto out;

		/*
		 * Verify upper root is exclusively associated with index dir.
		 * Older kernels stored upper fh in "trusted.overlay.origin"
		 * xattr. If that xattr exists, verify that it is a match to
		 * upper dir file handle. In any case, verify or set xattr
		 * "trusted.overlay.upper" to indicate that index may have
		 * directory entries.
		 */
		if (ovl_check_origin_xattr(ofs->indexdir)) {
			err = ovl_verify_set_fh(ofs->indexdir, OVL_XATTR_ORIGIN,
						upperpath->dentry, true, false);
			if (err)
				pr_err("overlayfs: failed to verify index dir 'origin' xattr\n");
		}
		err = ovl_verify_upper(ofs->indexdir, upperpath->dentry, true);
		if (err)
			pr_err("overlayfs: failed to verify index dir 'upper' xattr\n");

		/* Cleanup bad/stale/orphan index entries */
		if (!err)
			err = ovl_indexdir_cleanup(ofs);
	}
	if (err || !ofs->indexdir)
		pr_warn("overlayfs: try deleting index dir or mounting with '-o index=off' to disable inodes index.\n");

out:
	mnt_drop_write(mnt);
	return err;
}