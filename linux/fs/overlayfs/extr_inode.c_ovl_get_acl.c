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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_FS_POSIX_ACL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_POSIXACL (struct inode*) ; 
 struct posix_acl* get_acl (struct inode*,int) ; 
 struct inode* ovl_inode_real (struct inode*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

struct posix_acl *ovl_get_acl(struct inode *inode, int type)
{
	struct inode *realinode = ovl_inode_real(inode);
	const struct cred *old_cred;
	struct posix_acl *acl;

	if (!IS_ENABLED(CONFIG_FS_POSIX_ACL) || !IS_POSIXACL(realinode))
		return NULL;

	old_cred = ovl_override_creds(inode->i_sb);
	acl = get_acl(realinode, type);
	revert_creds(old_cred);

	return acl;
}