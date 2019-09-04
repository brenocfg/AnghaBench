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
struct ovl_fs {int /*<<< orphan*/  upper_mnt; } ;
struct ovl_fh {int dummy; } ;
typedef  struct ovl_fh dentry ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct ovl_fh* ERR_CAST (struct ovl_fh*) ; 
 struct ovl_fh* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 scalar_t__ IS_ERR_OR_NULL (struct ovl_fh*) ; 
 int /*<<< orphan*/  OVL_XATTR_UPPER ; 
 int /*<<< orphan*/  d_is_dir (struct ovl_fh*) ; 
 struct ovl_fh* dget (struct ovl_fh*) ; 
 int /*<<< orphan*/  dput (struct ovl_fh*) ; 
 int /*<<< orphan*/  kfree (struct ovl_fh*) ; 
 struct ovl_fh* ovl_decode_real_fh (struct ovl_fh*,int /*<<< orphan*/ ,int) ; 
 struct ovl_fh* ovl_get_fh (struct ovl_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,struct ovl_fh*,struct ovl_fh*) ; 

struct dentry *ovl_index_upper(struct ovl_fs *ofs, struct dentry *index)
{
	struct ovl_fh *fh;
	struct dentry *upper;

	if (!d_is_dir(index))
		return dget(index);

	fh = ovl_get_fh(index, OVL_XATTR_UPPER);
	if (IS_ERR_OR_NULL(fh))
		return ERR_CAST(fh);

	upper = ovl_decode_real_fh(fh, ofs->upper_mnt, true);
	kfree(fh);

	if (IS_ERR_OR_NULL(upper))
		return upper ?: ERR_PTR(-ESTALE);

	if (!d_is_dir(upper)) {
		pr_warn_ratelimited("overlayfs: invalid index upper (%pd2, upper=%pd2).\n",
				    index, upper);
		dput(upper);
		return ERR_PTR(-EIO);
	}

	return upper;
}