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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_uid; } ;
struct file_lock {TYPE_1__* fl_lmops; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lm_break; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_LEASE ; 
 int EACCES ; 
 int EINVAL ; 
 int ENOLCK ; 
#define  F_RDLCK 130 
#define  F_UNLCK 129 
#define  F_WRLCK 128 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int generic_add_lease (struct file*,long,struct file_lock**,void**) ; 
 int generic_delete_lease (struct file*,void*) ; 
 struct inode* locks_inode (struct file*) ; 
 int security_file_lock (struct file*,long) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int generic_setlease(struct file *filp, long arg, struct file_lock **flp,
			void **priv)
{
	struct inode *inode = locks_inode(filp);
	int error;

	if ((!uid_eq(current_fsuid(), inode->i_uid)) && !capable(CAP_LEASE))
		return -EACCES;
	if (!S_ISREG(inode->i_mode))
		return -EINVAL;
	error = security_file_lock(filp, arg);
	if (error)
		return error;

	switch (arg) {
	case F_UNLCK:
		return generic_delete_lease(filp, *priv);
	case F_RDLCK:
	case F_WRLCK:
		if (!(*flp)->fl_lmops->lm_break) {
			WARN_ON_ONCE(1);
			return -ENOLCK;
		}

		return generic_add_lease(filp, arg, flp, priv);
	default:
		return -EINVAL;
	}
}