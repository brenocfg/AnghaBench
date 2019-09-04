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
struct posix_acl {int /*<<< orphan*/  a_count; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GFS2_EATYPE_SYS ; 
 int __gfs2_xattr_set (struct inode*,char const*,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* gfs2_acl_name (int) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int posix_acl_to_xattr (int /*<<< orphan*/ *,struct posix_acl*,char*,size_t) ; 
 size_t posix_acl_xattr_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

int __gfs2_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	int error;
	size_t len;
	char *data;
	const char *name = gfs2_acl_name(type);

	if (acl) {
		len = posix_acl_xattr_size(acl->a_count);
		data = kmalloc(len, GFP_NOFS);
		if (data == NULL)
			return -ENOMEM;
		error = posix_acl_to_xattr(&init_user_ns, acl, data, len);
		if (error < 0)
			goto out;
	} else {
		data = NULL;
		len = 0;
	}

	error = __gfs2_xattr_set(inode, name, data, len, 0, GFS2_EATYPE_SYS);
	if (error)
		goto out;
	set_cached_acl(inode, type, acl);
out:
	kfree(data);
	return error;
}