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

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  OVL_XATTR_REDIRECT ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int ovl_getxattr (struct dentry*,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strchrnul (char*,char) ; 

char *ovl_get_redirect_xattr(struct dentry *dentry, int padding)
{
	int res;
	char *s, *next, *buf = NULL;

	res = ovl_getxattr(dentry, OVL_XATTR_REDIRECT, &buf, padding + 1);
	if (res == -ENODATA)
		return NULL;
	if (res < 0)
		return ERR_PTR(res);
	if (res == 0)
		goto invalid;

	if (buf[0] == '/') {
		for (s = buf; *s++ == '/'; s = next) {
			next = strchrnul(s, '/');
			if (s == next)
				goto invalid;
		}
	} else {
		if (strchr(buf, '/') != NULL)
			goto invalid;
	}

	return buf;
invalid:
	pr_warn_ratelimited("overlayfs: invalid redirect (%s)\n", buf);
	res = -EINVAL;
	kfree(buf);
	return ERR_PTR(res);
}