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
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_CHOWN ; 
 int /*<<< orphan*/  INVALID_UID ; 
 scalar_t__ capable_wrt_inode_uidgid (struct inode const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 scalar_t__ ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool chown_ok(const struct inode *inode, kuid_t uid)
{
	if (uid_eq(current_fsuid(), inode->i_uid) &&
	    uid_eq(uid, inode->i_uid))
		return true;
	if (capable_wrt_inode_uidgid(inode, CAP_CHOWN))
		return true;
	if (uid_eq(inode->i_uid, INVALID_UID) &&
	    ns_capable(inode->i_sb->s_user_ns, CAP_CHOWN))
		return true;
	return false;
}