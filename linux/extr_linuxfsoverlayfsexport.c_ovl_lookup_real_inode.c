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
struct ovl_layer {scalar_t__ idx; int /*<<< orphan*/  mnt; } ;
struct ovl_fs {scalar_t__ indexdir; int /*<<< orphan*/  upper_mnt; } ;
struct inode {int dummy; } ;
typedef  struct inode dentry ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct inode* ERR_CAST (struct inode*) ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct inode*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct inode* d_find_any_alias (struct inode*) ; 
 int /*<<< orphan*/  d_is_dir (struct inode*) ; 
 int /*<<< orphan*/  dput (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* ovl_dentry_real_at (struct inode*,scalar_t__) ; 
 struct inode* ovl_index_upper (struct ovl_fs*,struct inode*) ; 
 struct inode* ovl_lookup_index (struct ovl_fs*,int /*<<< orphan*/ *,struct inode*,int) ; 
 struct inode* ovl_lookup_inode (struct super_block*,struct inode*,int) ; 
 struct inode* ovl_lookup_real (struct super_block*,struct inode*,struct ovl_layer*) ; 

__attribute__((used)) static struct dentry *ovl_lookup_real_inode(struct super_block *sb,
					    struct dentry *real,
					    struct ovl_layer *layer)
{
	struct ovl_fs *ofs = sb->s_fs_info;
	struct ovl_layer upper_layer = { .mnt = ofs->upper_mnt };
	struct dentry *index = NULL;
	struct dentry *this = NULL;
	struct inode *inode;

	/*
	 * Decoding upper dir from index is expensive, so first try to lookup
	 * overlay dentry in inode/dcache.
	 */
	inode = ovl_lookup_inode(sb, real, !layer->idx);
	if (IS_ERR(inode))
		return ERR_CAST(inode);
	if (inode) {
		this = d_find_any_alias(inode);
		iput(inode);
	}

	/*
	 * For decoded lower dir file handle, lookup index by origin to check
	 * if lower dir was copied up and and/or removed.
	 */
	if (!this && layer->idx && ofs->indexdir && !WARN_ON(!d_is_dir(real))) {
		index = ovl_lookup_index(ofs, NULL, real, false);
		if (IS_ERR(index))
			return index;
	}

	/* Get connected upper overlay dir from index */
	if (index) {
		struct dentry *upper = ovl_index_upper(ofs, index);

		dput(index);
		if (IS_ERR_OR_NULL(upper))
			return upper;

		/*
		 * ovl_lookup_real() in lower layer may call recursively once to
		 * ovl_lookup_real() in upper layer. The first level call walks
		 * back lower parents to the topmost indexed parent. The second
		 * recursive call walks back from indexed upper to the topmost
		 * connected/hashed upper parent (or up to root).
		 */
		this = ovl_lookup_real(sb, upper, &upper_layer);
		dput(upper);
	}

	if (IS_ERR_OR_NULL(this))
		return this;

	if (WARN_ON(ovl_dentry_real_at(this, layer->idx) != real)) {
		dput(this);
		this = ERR_PTR(-EIO);
	}

	return this;
}