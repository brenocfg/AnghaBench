#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {TYPE_1__* mnt_sb; } ;
struct fid {int dummy; } ;
struct export_operations {struct dentry* (* fh_to_parent ) (TYPE_1__*,struct fid*,int,int) ;struct dentry* (* fh_to_dentry ) (TYPE_1__*,struct fid*,int,int) ;} ;
struct dentry {int d_flags; scalar_t__ d_inode; } ;
struct TYPE_3__ {struct export_operations* s_export_op; } ;

/* Variables and functions */
 int DCACHE_DISCONNECTED ; 
 int EACCES ; 
 int ENOMEM ; 
 struct dentry* ERR_CAST (struct dentry*) ; 
 struct dentry* ERR_PTR (int) ; 
 int ESTALE ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int PTR_ERR (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int exportfs_get_name (struct vfsmount*,struct dentry*,char*,struct dentry*) ; 
 struct dentry* find_acceptable_alias (struct dentry*,int (*) (void*,struct dentry*),void*) ; 
 int /*<<< orphan*/  inode_lock (scalar_t__) ; 
 int /*<<< orphan*/  inode_unlock (scalar_t__) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int reconnect_path (struct vfsmount*,struct dentry*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 struct dentry* stub1 (TYPE_1__*,struct fid*,int,int) ; 
 struct dentry* stub2 (TYPE_1__*,struct fid*,int,int) ; 

struct dentry *exportfs_decode_fh(struct vfsmount *mnt, struct fid *fid,
		int fh_len, int fileid_type,
		int (*acceptable)(void *, struct dentry *), void *context)
{
	const struct export_operations *nop = mnt->mnt_sb->s_export_op;
	struct dentry *result, *alias;
	char nbuf[NAME_MAX+1];
	int err;

	/*
	 * Try to get any dentry for the given file handle from the filesystem.
	 */
	if (!nop || !nop->fh_to_dentry)
		return ERR_PTR(-ESTALE);
	result = nop->fh_to_dentry(mnt->mnt_sb, fid, fh_len, fileid_type);
	if (PTR_ERR(result) == -ENOMEM)
		return ERR_CAST(result);
	if (IS_ERR_OR_NULL(result))
		return ERR_PTR(-ESTALE);

	/*
	 * If no acceptance criteria was specified by caller, a disconnected
	 * dentry is also accepatable. Callers may use this mode to query if
	 * file handle is stale or to get a reference to an inode without
	 * risking the high overhead caused by directory reconnect.
	 */
	if (!acceptable)
		return result;

	if (d_is_dir(result)) {
		/*
		 * This request is for a directory.
		 *
		 * On the positive side there is only one dentry for each
		 * directory inode.  On the negative side this implies that we
		 * to ensure our dentry is connected all the way up to the
		 * filesystem root.
		 */
		if (result->d_flags & DCACHE_DISCONNECTED) {
			err = reconnect_path(mnt, result, nbuf);
			if (err)
				goto err_result;
		}

		if (!acceptable(context, result)) {
			err = -EACCES;
			goto err_result;
		}

		return result;
	} else {
		/*
		 * It's not a directory.  Life is a little more complicated.
		 */
		struct dentry *target_dir, *nresult;

		/*
		 * See if either the dentry we just got from the filesystem
		 * or any alias for it is acceptable.  This is always true
		 * if this filesystem is exported without the subtreecheck
		 * option.  If the filesystem is exported with the subtree
		 * check option there's a fair chance we need to look at
		 * the parent directory in the file handle and make sure
		 * it's connected to the filesystem root.
		 */
		alias = find_acceptable_alias(result, acceptable, context);
		if (alias)
			return alias;

		/*
		 * Try to extract a dentry for the parent directory from the
		 * file handle.  If this fails we'll have to give up.
		 */
		err = -ESTALE;
		if (!nop->fh_to_parent)
			goto err_result;

		target_dir = nop->fh_to_parent(mnt->mnt_sb, fid,
				fh_len, fileid_type);
		if (!target_dir)
			goto err_result;
		err = PTR_ERR(target_dir);
		if (IS_ERR(target_dir))
			goto err_result;

		/*
		 * And as usual we need to make sure the parent directory is
		 * connected to the filesystem root.  The VFS really doesn't
		 * like disconnected directories..
		 */
		err = reconnect_path(mnt, target_dir, nbuf);
		if (err) {
			dput(target_dir);
			goto err_result;
		}

		/*
		 * Now that we've got both a well-connected parent and a
		 * dentry for the inode we're after, make sure that our
		 * inode is actually connected to the parent.
		 */
		err = exportfs_get_name(mnt, target_dir, nbuf, result);
		if (!err) {
			inode_lock(target_dir->d_inode);
			nresult = lookup_one_len(nbuf, target_dir,
						 strlen(nbuf));
			inode_unlock(target_dir->d_inode);
			if (!IS_ERR(nresult)) {
				if (nresult->d_inode) {
					dput(result);
					result = nresult;
				} else
					dput(nresult);
			}
		}

		/*
		 * At this point we are done with the parent, but it's pinned
		 * by the child dentry anyway.
		 */
		dput(target_dir);

		/*
		 * And finally make sure the dentry is actually acceptable
		 * to NFSD.
		 */
		alias = find_acceptable_alias(result, acceptable, context);
		if (!alias) {
			err = -EACCES;
			goto err_result;
		}

		return alias;
	}

 err_result:
	dput(result);
	if (err != -ENOMEM)
		err = -ESTALE;
	return ERR_PTR(err);
}