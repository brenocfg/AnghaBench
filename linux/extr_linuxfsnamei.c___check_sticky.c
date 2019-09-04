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
struct inode {int /*<<< orphan*/  i_uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FOWNER ; 
 int /*<<< orphan*/  capable_wrt_inode_uidgid (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __check_sticky(struct inode *dir, struct inode *inode)
{
	kuid_t fsuid = current_fsuid();

	if (uid_eq(inode->i_uid, fsuid))
		return 0;
	if (uid_eq(dir->i_uid, fsuid))
		return 0;
	return !capable_wrt_inode_uidgid(inode, CAP_FOWNER);
}