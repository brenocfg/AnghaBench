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
struct ovl_fh {int /*<<< orphan*/  len; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ovl_fh const*) ; 
 int /*<<< orphan*/  OVL_XATTR_ORIGIN ; 
 int PTR_ERR (struct ovl_fh const*) ; 
 int /*<<< orphan*/  kfree (struct ovl_fh const*) ; 
 scalar_t__ ovl_can_decode_fh (int /*<<< orphan*/ ) ; 
 int ovl_check_setxattr (struct dentry*,struct dentry*,int /*<<< orphan*/ ,struct ovl_fh const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ovl_fh* ovl_encode_real_fh (struct dentry*,int) ; 

int ovl_set_origin(struct dentry *dentry, struct dentry *lower,
		   struct dentry *upper)
{
	const struct ovl_fh *fh = NULL;
	int err;

	/*
	 * When lower layer doesn't support export operations store a 'null' fh,
	 * so we can use the overlay.origin xattr to distignuish between a copy
	 * up and a pure upper inode.
	 */
	if (ovl_can_decode_fh(lower->d_sb)) {
		fh = ovl_encode_real_fh(lower, false);
		if (IS_ERR(fh))
			return PTR_ERR(fh);
	}

	/*
	 * Do not fail when upper doesn't support xattrs.
	 */
	err = ovl_check_setxattr(dentry, upper, OVL_XATTR_ORIGIN, fh,
				 fh ? fh->len : 0, 0);
	kfree(fh);

	return err;
}