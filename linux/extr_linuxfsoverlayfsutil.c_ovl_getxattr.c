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
struct dentry {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENODATA ; 
 size_t ENOMEM ; 
 size_t EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,char*,size_t) ; 
 size_t vfs_getxattr (struct dentry*,char*,char*,size_t) ; 

ssize_t ovl_getxattr(struct dentry *dentry, char *name, char **value,
		     size_t padding)
{
	ssize_t res;
	char *buf = NULL;

	res = vfs_getxattr(dentry, name, NULL, 0);
	if (res < 0) {
		if (res == -ENODATA || res == -EOPNOTSUPP)
			return -ENODATA;
		goto fail;
	}

	if (res != 0) {
		buf = kzalloc(res + padding, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;

		res = vfs_getxattr(dentry, name, buf, res);
		if (res < 0)
			goto fail;
	}
	*value = buf;

	return res;

fail:
	pr_warn_ratelimited("overlayfs: failed to get xattr %s: err=%zi)\n",
			    name, res);
	kfree(buf);
	return res;
}