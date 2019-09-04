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
struct ovl_fh {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int EOPNOTSUPP ; 
 struct ovl_fh* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ovl_fh*) ; 
 struct ovl_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ovl_check_fh_len (struct ovl_fh*,int) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int,...) ; 
 int vfs_getxattr (struct dentry*,char const*,struct ovl_fh*,int) ; 

__attribute__((used)) static struct ovl_fh *ovl_get_fh(struct dentry *dentry, const char *name)
{
	int res, err;
	struct ovl_fh *fh = NULL;

	res = vfs_getxattr(dentry, name, NULL, 0);
	if (res < 0) {
		if (res == -ENODATA || res == -EOPNOTSUPP)
			return NULL;
		goto fail;
	}
	/* Zero size value means "copied up but origin unknown" */
	if (res == 0)
		return NULL;

	fh = kzalloc(res, GFP_KERNEL);
	if (!fh)
		return ERR_PTR(-ENOMEM);

	res = vfs_getxattr(dentry, name, fh, res);
	if (res < 0)
		goto fail;

	err = ovl_check_fh_len(fh, res);
	if (err < 0) {
		if (err == -ENODATA)
			goto out;
		goto invalid;
	}

	return fh;

out:
	kfree(fh);
	return NULL;

fail:
	pr_warn_ratelimited("overlayfs: failed to get origin (%i)\n", res);
	goto out;
invalid:
	pr_warn_ratelimited("overlayfs: invalid origin (%*phN)\n", res, fh);
	goto out;
}