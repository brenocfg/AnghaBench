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
typedef  int u32 ;
struct path {scalar_t__ dentry; } ;
struct ovl_layer {int dummy; } ;
struct kstat {int nlink; int /*<<< orphan*/  blocks; int /*<<< orphan*/  ino; } ;
struct dentry {TYPE_1__* d_inode; int /*<<< orphan*/  d_sb; } ;
struct cred {int dummy; } ;
typedef  enum ovl_path_type { ____Placeholder_ovl_path_type } ovl_path_type ;
struct TYPE_2__ {int i_nlink; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVL_INDEX ; 
 scalar_t__ OVL_TYPE_MERGE (int) ; 
 scalar_t__ OVL_TYPE_ORIGIN (int) ; 
 int /*<<< orphan*/  OVL_TYPE_UPPER (int) ; 
 int STATX_BLOCKS ; 
 int STATX_INO ; 
 int STATX_NLINK ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ ovl_dentry_lowerdata (struct dentry*) ; 
 int ovl_is_metacopy_dentry (struct dentry*) ; 
 struct ovl_layer* ovl_layer_lower (struct dentry*) ; 
 int ovl_map_dev_ino (struct dentry*,struct kstat*,struct ovl_layer*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_path_lower (struct dentry*,struct path*) ; 
 int /*<<< orphan*/  ovl_path_lowerdata (struct dentry*,struct path*) ; 
 int ovl_path_real (struct dentry*,struct path*) ; 
 int ovl_same_sb (int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_verify_lower (int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_xino_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int vfs_getattr (struct path*,struct kstat*,int,unsigned int) ; 

int ovl_getattr(const struct path *path, struct kstat *stat,
		u32 request_mask, unsigned int flags)
{
	struct dentry *dentry = path->dentry;
	enum ovl_path_type type;
	struct path realpath;
	const struct cred *old_cred;
	bool is_dir = S_ISDIR(dentry->d_inode->i_mode);
	bool samefs = ovl_same_sb(dentry->d_sb);
	struct ovl_layer *lower_layer = NULL;
	int err;
	bool metacopy_blocks = false;

	metacopy_blocks = ovl_is_metacopy_dentry(dentry);

	type = ovl_path_real(dentry, &realpath);
	old_cred = ovl_override_creds(dentry->d_sb);
	err = vfs_getattr(&realpath, stat, request_mask, flags);
	if (err)
		goto out;

	/*
	 * For non-dir or same fs, we use st_ino of the copy up origin.
	 * This guaranties constant st_dev/st_ino across copy up.
	 * With xino feature and non-samefs, we use st_ino of the copy up
	 * origin masked with high bits that represent the layer id.
	 *
	 * If lower filesystem supports NFS file handles, this also guaranties
	 * persistent st_ino across mount cycle.
	 */
	if (!is_dir || samefs || ovl_xino_bits(dentry->d_sb)) {
		if (!OVL_TYPE_UPPER(type)) {
			lower_layer = ovl_layer_lower(dentry);
		} else if (OVL_TYPE_ORIGIN(type)) {
			struct kstat lowerstat;
			u32 lowermask = STATX_INO | STATX_BLOCKS |
					(!is_dir ? STATX_NLINK : 0);

			ovl_path_lower(dentry, &realpath);
			err = vfs_getattr(&realpath, &lowerstat,
					  lowermask, flags);
			if (err)
				goto out;

			/*
			 * Lower hardlinks may be broken on copy up to different
			 * upper files, so we cannot use the lower origin st_ino
			 * for those different files, even for the same fs case.
			 *
			 * Similarly, several redirected dirs can point to the
			 * same dir on a lower layer. With the "verify_lower"
			 * feature, we do not use the lower origin st_ino, if
			 * we haven't verified that this redirect is unique.
			 *
			 * With inodes index enabled, it is safe to use st_ino
			 * of an indexed origin. The index validates that the
			 * upper hardlink is not broken and that a redirected
			 * dir is the only redirect to that origin.
			 */
			if (ovl_test_flag(OVL_INDEX, d_inode(dentry)) ||
			    (!ovl_verify_lower(dentry->d_sb) &&
			     (is_dir || lowerstat.nlink == 1))) {
				stat->ino = lowerstat.ino;
				lower_layer = ovl_layer_lower(dentry);
			}

			/*
			 * If we are querying a metacopy dentry and lower
			 * dentry is data dentry, then use the blocks we
			 * queried just now. We don't have to do additional
			 * vfs_getattr(). If lower itself is metacopy, then
			 * additional vfs_getattr() is unavoidable.
			 */
			if (metacopy_blocks &&
			    realpath.dentry == ovl_dentry_lowerdata(dentry)) {
				stat->blocks = lowerstat.blocks;
				metacopy_blocks = false;
			}
		}

		if (metacopy_blocks) {
			/*
			 * If lower is not same as lowerdata or if there was
			 * no origin on upper, we can end up here.
			 */
			struct kstat lowerdatastat;
			u32 lowermask = STATX_BLOCKS;

			ovl_path_lowerdata(dentry, &realpath);
			err = vfs_getattr(&realpath, &lowerdatastat,
					  lowermask, flags);
			if (err)
				goto out;
			stat->blocks = lowerdatastat.blocks;
		}
	}

	err = ovl_map_dev_ino(dentry, stat, lower_layer);
	if (err)
		goto out;

	/*
	 * It's probably not worth it to count subdirs to get the
	 * correct link count.  nlink=1 seems to pacify 'find' and
	 * other utilities.
	 */
	if (is_dir && OVL_TYPE_MERGE(type))
		stat->nlink = 1;

	/*
	 * Return the overlay inode nlinks for indexed upper inodes.
	 * Overlay inode nlink counts the union of the upper hardlinks
	 * and non-covered lower hardlinks. It does not include the upper
	 * index hardlink.
	 */
	if (!is_dir && ovl_test_flag(OVL_INDEX, d_inode(dentry)))
		stat->nlink = dentry->d_inode->i_nlink;

out:
	revert_creds(old_cred);

	return err;
}