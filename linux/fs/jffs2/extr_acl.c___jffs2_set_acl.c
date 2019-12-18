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
struct inode {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 int do_jffs2_setxattr (struct inode*,int,char*,char*,size_t,int /*<<< orphan*/ ) ; 
 char* jffs2_acl_to_medium (struct posix_acl*,size_t*) ; 
 int /*<<< orphan*/  kfree (char*) ; 

__attribute__((used)) static int __jffs2_set_acl(struct inode *inode, int xprefix, struct posix_acl *acl)
{
	char *value = NULL;
	size_t size = 0;
	int rc;

	if (acl) {
		value = jffs2_acl_to_medium(acl, &size);
		if (IS_ERR(value))
			return PTR_ERR(value);
	}
	rc = do_jffs2_setxattr(inode, xprefix, "", value, size, 0);
	if (!value && rc == -ENODATA)
		rc = 0;
	kfree(value);

	return rc;
}