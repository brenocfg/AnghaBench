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
struct super_block {struct ovl_fs* s_fs_info; } ;
struct ovl_path {struct inode* dentry; } ;
struct ovl_fs {scalar_t__ indexdir; } ;
struct ovl_fh {int dummy; } ;
struct inode {int d_flags; } ;
struct dentry {int d_flags; } ;

/* Variables and functions */
 int DCACHE_DISCONNECTED ; 
 struct inode* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 struct inode* d_find_any_alias (struct inode*) ; 
 scalar_t__ d_is_dir (struct inode*) ; 
 int /*<<< orphan*/  dput (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int ovl_check_origin_fh (struct ovl_fs*,struct ovl_fh*,int,int /*<<< orphan*/ *,struct ovl_path**) ; 
 struct inode* ovl_get_dentry (struct super_block*,struct inode*,struct ovl_path*,struct inode*) ; 
 struct inode* ovl_get_index_fh (struct ovl_fs*,struct ovl_fh*) ; 
 struct inode* ovl_index_upper (struct ovl_fs*,struct inode*) ; 
 struct inode* ovl_lookup_inode (struct super_block*,struct inode*,int) ; 
 int ovl_verify_origin (struct inode*,struct inode*,int) ; 

__attribute__((used)) static struct dentry *ovl_lower_fh_to_d(struct super_block *sb,
					struct ovl_fh *fh)
{
	struct ovl_fs *ofs = sb->s_fs_info;
	struct ovl_path origin = { };
	struct ovl_path *stack = &origin;
	struct dentry *dentry = NULL;
	struct dentry *index = NULL;
	struct inode *inode;
	int err;

	/* First lookup overlay inode in inode cache by origin fh */
	err = ovl_check_origin_fh(ofs, fh, false, NULL, &stack);
	if (err)
		return ERR_PTR(err);

	if (!d_is_dir(origin.dentry) ||
	    !(origin.dentry->d_flags & DCACHE_DISCONNECTED)) {
		inode = ovl_lookup_inode(sb, origin.dentry, false);
		err = PTR_ERR(inode);
		if (IS_ERR(inode))
			goto out_err;
		if (inode) {
			dentry = d_find_any_alias(inode);
			iput(inode);
			if (dentry)
				goto out;
		}
	}

	/* Then lookup indexed upper/whiteout by origin fh */
	if (ofs->indexdir) {
		index = ovl_get_index_fh(ofs, fh);
		err = PTR_ERR(index);
		if (IS_ERR(index)) {
			index = NULL;
			goto out_err;
		}
	}

	/* Then try to get a connected upper dir by index */
	if (index && d_is_dir(index)) {
		struct dentry *upper = ovl_index_upper(ofs, index);

		err = PTR_ERR(upper);
		if (IS_ERR_OR_NULL(upper))
			goto out_err;

		dentry = ovl_get_dentry(sb, upper, NULL, NULL);
		dput(upper);
		goto out;
	}

	/* Find origin.dentry again with ovl_acceptable() layer check */
	if (d_is_dir(origin.dentry)) {
		dput(origin.dentry);
		origin.dentry = NULL;
		err = ovl_check_origin_fh(ofs, fh, true, NULL, &stack);
		if (err)
			goto out_err;
	}
	if (index) {
		err = ovl_verify_origin(index, origin.dentry, false);
		if (err)
			goto out_err;
	}

	/* Get a connected non-upper dir or disconnected non-dir */
	dentry = ovl_get_dentry(sb, NULL, &origin, index);

out:
	dput(origin.dentry);
	dput(index);
	return dentry;

out_err:
	dentry = ERR_PTR(err);
	goto out;
}