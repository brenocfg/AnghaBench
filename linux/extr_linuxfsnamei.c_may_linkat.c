#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_1__* dentry; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int EPERM ; 
 int /*<<< orphan*/  audit_log_link_denied (char*) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ inode_owner_or_capable (struct inode*) ; 
 scalar_t__ safe_hardlink_source (struct inode*) ; 
 int /*<<< orphan*/  sysctl_protected_hardlinks ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int may_linkat(struct path *link)
{
	struct inode *inode = link->dentry->d_inode;

	/* Inode writeback is not safe when the uid or gid are invalid. */
	if (!uid_valid(inode->i_uid) || !gid_valid(inode->i_gid))
		return -EOVERFLOW;

	if (!sysctl_protected_hardlinks)
		return 0;

	/* Source inode owner (or CAP_FOWNER) can hardlink all they like,
	 * otherwise, it must be a safe source.
	 */
	if (safe_hardlink_source(inode) || inode_owner_or_capable(inode))
		return 0;

	audit_log_link_denied("linkat");
	return -EPERM;
}