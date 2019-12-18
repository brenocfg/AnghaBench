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
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int EINVAL ; 
 int ENODATA ; 
 int ENOMEM ; 
 int ENOSYS ; 
 struct posix_acl* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GOSSIP_ACL_DEBUG ; 
 int /*<<< orphan*/  ORANGEFS_MAX_XATTR_VALUELEN ; 
 char* XATTR_NAME_POSIX_ACL_ACCESS ; 
 char* XATTR_NAME_POSIX_ACL_DEFAULT ; 
 int /*<<< orphan*/  get_khandle_from_ino (struct inode*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gossip_err (char*,int,...) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int orangefs_inode_getxattr (struct inode*,char*,char*,int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_from_xattr (int /*<<< orphan*/ *,char*,int) ; 

struct posix_acl *orangefs_get_acl(struct inode *inode, int type)
{
	struct posix_acl *acl;
	int ret;
	char *key = NULL, *value = NULL;

	switch (type) {
	case ACL_TYPE_ACCESS:
		key = XATTR_NAME_POSIX_ACL_ACCESS;
		break;
	case ACL_TYPE_DEFAULT:
		key = XATTR_NAME_POSIX_ACL_DEFAULT;
		break;
	default:
		gossip_err("orangefs_get_acl: bogus value of type %d\n", type);
		return ERR_PTR(-EINVAL);
	}
	/*
	 * Rather than incurring a network call just to determine the exact
	 * length of the attribute, I just allocate a max length to save on
	 * the network call. Conceivably, we could pass NULL to
	 * orangefs_inode_getxattr() to probe the length of the value, but
	 * I don't do that for now.
	 */
	value = kmalloc(ORANGEFS_MAX_XATTR_VALUELEN, GFP_KERNEL);
	if (!value)
		return ERR_PTR(-ENOMEM);

	gossip_debug(GOSSIP_ACL_DEBUG,
		     "inode %pU, key %s, type %d\n",
		     get_khandle_from_ino(inode),
		     key,
		     type);
	ret = orangefs_inode_getxattr(inode, key, value,
				      ORANGEFS_MAX_XATTR_VALUELEN);
	/* if the key exists, convert it to an in-memory rep */
	if (ret > 0) {
		acl = posix_acl_from_xattr(&init_user_ns, value, ret);
	} else if (ret == -ENODATA || ret == -ENOSYS) {
		acl = NULL;
	} else {
		gossip_err("inode %pU retrieving acl's failed with error %d\n",
			   get_khandle_from_ino(inode),
			   ret);
		acl = ERR_PTR(ret);
	}
	/* kfree(NULL) is safe, so don't worry if value ever got used */
	kfree(value);
	return acl;
}