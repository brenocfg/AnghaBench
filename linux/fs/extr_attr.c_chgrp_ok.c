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
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
typedef  int /*<<< orphan*/  kgid_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_CHOWN ; 
 int /*<<< orphan*/  INVALID_GID ; 
 scalar_t__ capable_wrt_inode_uidgid (struct inode const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 scalar_t__ gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ in_group_p (int /*<<< orphan*/ ) ; 
 scalar_t__ ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool chgrp_ok(const struct inode *inode, kgid_t gid)
{
	if (uid_eq(current_fsuid(), inode->i_uid) &&
	    (in_group_p(gid) || gid_eq(gid, inode->i_gid)))
		return true;
	if (capable_wrt_inode_uidgid(inode, CAP_CHOWN))
		return true;
	if (gid_eq(inode->i_gid, INVALID_GID) &&
	    ns_capable(inode->i_sb->s_user_ns, CAP_CHOWN))
		return true;
	return false;
}