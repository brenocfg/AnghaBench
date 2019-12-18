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
struct ovl_fh {scalar_t__ len; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int ESTALE ; 
 scalar_t__ IS_ERR (struct ovl_fh*) ; 
 int PTR_ERR (struct ovl_fh*) ; 
 int /*<<< orphan*/  kfree (struct ovl_fh*) ; 
 scalar_t__ memcmp (struct ovl_fh const*,struct ovl_fh*,scalar_t__) ; 
 struct ovl_fh* ovl_get_fh (struct dentry*,char const*) ; 

__attribute__((used)) static int ovl_verify_fh(struct dentry *dentry, const char *name,
			 const struct ovl_fh *fh)
{
	struct ovl_fh *ofh = ovl_get_fh(dentry, name);
	int err = 0;

	if (!ofh)
		return -ENODATA;

	if (IS_ERR(ofh))
		return PTR_ERR(ofh);

	if (fh->len != ofh->len || memcmp(fh, ofh, fh->len))
		err = -ESTALE;

	kfree(ofh);
	return err;
}