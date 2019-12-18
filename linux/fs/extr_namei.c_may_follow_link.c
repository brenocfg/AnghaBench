#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nameidata {int flags; TYPE_2__* stack; int /*<<< orphan*/  name; struct inode* inode; struct inode* link_inode; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
struct TYPE_6__ {int /*<<< orphan*/  fsuid; } ;
struct TYPE_4__ {int /*<<< orphan*/  dentry; } ;
struct TYPE_5__ {TYPE_1__ link; } ;

/* Variables and functions */
 int EACCES ; 
 int ECHILD ; 
 int LOOKUP_RCU ; 
 int S_ISVTX ; 
 int S_IWOTH ; 
 int /*<<< orphan*/  audit_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_link_denied (char*) ; 
 TYPE_3__* current_cred () ; 
 int /*<<< orphan*/  sysctl_protected_symlinks ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int may_follow_link(struct nameidata *nd)
{
	const struct inode *inode;
	const struct inode *parent;
	kuid_t puid;

	if (!sysctl_protected_symlinks)
		return 0;

	/* Allowed if owner and follower match. */
	inode = nd->link_inode;
	if (uid_eq(current_cred()->fsuid, inode->i_uid))
		return 0;

	/* Allowed if parent directory not sticky and world-writable. */
	parent = nd->inode;
	if ((parent->i_mode & (S_ISVTX|S_IWOTH)) != (S_ISVTX|S_IWOTH))
		return 0;

	/* Allowed if parent directory and link owner match. */
	puid = parent->i_uid;
	if (uid_valid(puid) && uid_eq(puid, inode->i_uid))
		return 0;

	if (nd->flags & LOOKUP_RCU)
		return -ECHILD;

	audit_inode(nd->name, nd->stack[0].link.dentry, 0);
	audit_log_link_denied("follow_link");
	return -EACCES;
}