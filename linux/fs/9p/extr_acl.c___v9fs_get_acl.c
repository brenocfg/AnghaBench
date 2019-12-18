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
struct posix_acl {int dummy; } ;
struct p9_fid {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENODATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct posix_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_from_xattr (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v9fs_fid_xattr_get (struct p9_fid*,char*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct posix_acl *__v9fs_get_acl(struct p9_fid *fid, char *name)
{
	ssize_t size;
	void *value = NULL;
	struct posix_acl *acl = NULL;

	size = v9fs_fid_xattr_get(fid, name, NULL, 0);
	if (size > 0) {
		value = kzalloc(size, GFP_NOFS);
		if (!value)
			return ERR_PTR(-ENOMEM);
		size = v9fs_fid_xattr_get(fid, name, value, size);
		if (size > 0) {
			acl = posix_acl_from_xattr(&init_user_ns, value, size);
			if (IS_ERR(acl))
				goto err_out;
		}
	} else if (size == -ENODATA || size == 0 ||
		   size == -ENOSYS || size == -EOPNOTSUPP) {
		acl = NULL;
	} else
		acl = ERR_PTR(-EIO);

err_out:
	kfree(value);
	return acl;
}