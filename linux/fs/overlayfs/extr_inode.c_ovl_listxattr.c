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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct cred {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EIO ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  ovl_can_list (char*) ; 
 struct dentry* ovl_dentry_real (struct dentry*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int strnlen (char*,size_t) ; 
 size_t vfs_listxattr (struct dentry*,char*,size_t) ; 

ssize_t ovl_listxattr(struct dentry *dentry, char *list, size_t size)
{
	struct dentry *realdentry = ovl_dentry_real(dentry);
	ssize_t res;
	size_t len;
	char *s;
	const struct cred *old_cred;

	old_cred = ovl_override_creds(dentry->d_sb);
	res = vfs_listxattr(realdentry, list, size);
	revert_creds(old_cred);
	if (res <= 0 || size == 0)
		return res;

	/* filter out private xattrs */
	for (s = list, len = res; len;) {
		size_t slen = strnlen(s, len) + 1;

		/* underlying fs providing us with an broken xattr list? */
		if (WARN_ON(slen > len))
			return -EIO;

		len -= slen;
		if (!ovl_can_list(s)) {
			res -= slen;
			memmove(s, s + slen, len);
		} else {
			s += slen;
		}
	}

	return res;
}