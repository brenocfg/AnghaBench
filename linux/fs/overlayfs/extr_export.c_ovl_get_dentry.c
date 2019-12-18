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
struct ovl_path {struct dentry* dentry; struct ovl_layer* layer; } ;
struct ovl_layer {int /*<<< orphan*/  mnt; } ;
struct ovl_fs {int /*<<< orphan*/  upper_mnt; } ;
struct dentry {int d_flags; } ;

/* Variables and functions */
 int DCACHE_DISCONNECTED ; 
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 struct dentry* ovl_lookup_real (struct super_block*,struct dentry*,struct ovl_layer*) ; 
 struct dentry* ovl_obtain_alias (struct super_block*,struct dentry*,struct ovl_path*,struct dentry*) ; 

__attribute__((used)) static struct dentry *ovl_get_dentry(struct super_block *sb,
				     struct dentry *upper,
				     struct ovl_path *lowerpath,
				     struct dentry *index)
{
	struct ovl_fs *ofs = sb->s_fs_info;
	struct ovl_layer upper_layer = { .mnt = ofs->upper_mnt };
	struct ovl_layer *layer = upper ? &upper_layer : lowerpath->layer;
	struct dentry *real = upper ?: (index ?: lowerpath->dentry);

	/*
	 * Obtain a disconnected overlay dentry from a non-dir real dentry
	 * and index.
	 */
	if (!d_is_dir(real))
		return ovl_obtain_alias(sb, upper, lowerpath, index);

	/* Removed empty directory? */
	if ((real->d_flags & DCACHE_DISCONNECTED) || d_unhashed(real))
		return ERR_PTR(-ENOENT);

	/*
	 * If real dentry is connected and hashed, get a connected overlay
	 * dentry whose real dentry is @real.
	 */
	return ovl_lookup_real(sb, real, layer);
}