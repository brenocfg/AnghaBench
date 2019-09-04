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
struct ovl_fs {int /*<<< orphan*/  upper_mnt; } ;
struct ovl_fh {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* ovl_decode_real_fh (struct ovl_fh*,int /*<<< orphan*/ ,int) ; 
 struct dentry* ovl_get_dentry (struct super_block*,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *ovl_upper_fh_to_d(struct super_block *sb,
					struct ovl_fh *fh)
{
	struct ovl_fs *ofs = sb->s_fs_info;
	struct dentry *dentry;
	struct dentry *upper;

	if (!ofs->upper_mnt)
		return ERR_PTR(-EACCES);

	upper = ovl_decode_real_fh(fh, ofs->upper_mnt, true);
	if (IS_ERR_OR_NULL(upper))
		return upper;

	dentry = ovl_get_dentry(sb, upper, NULL, NULL);
	dput(upper);

	return dentry;
}