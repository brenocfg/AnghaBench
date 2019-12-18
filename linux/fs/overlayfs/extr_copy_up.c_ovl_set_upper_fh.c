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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ovl_fh const*) ; 
 int /*<<< orphan*/  OVL_XATTR_UPPER ; 
 int PTR_ERR (struct ovl_fh const*) ; 
 int /*<<< orphan*/  kfree (struct ovl_fh const*) ; 
 int ovl_do_setxattr (struct dentry*,int /*<<< orphan*/ ,struct ovl_fh const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ovl_fh* ovl_encode_real_fh (struct dentry*,int) ; 

__attribute__((used)) static int ovl_set_upper_fh(struct dentry *upper, struct dentry *index)
{
	const struct ovl_fh *fh;
	int err;

	fh = ovl_encode_real_fh(upper, true);
	if (IS_ERR(fh))
		return PTR_ERR(fh);

	err = ovl_do_setxattr(index, OVL_XATTR_UPPER, fh, fh->len, 0);

	kfree(fh);
	return err;
}