#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* s_op; int /*<<< orphan*/  s_user_ns; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct super_block* i_sb; } ;
struct TYPE_3__ {int (* freeze_super ) (struct super_block*) ;int /*<<< orphan*/ * freeze_fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 TYPE_2__* file_inode (struct file*) ; 
 int freeze_super (struct super_block*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct super_block*) ; 

__attribute__((used)) static int ioctl_fsfreeze(struct file *filp)
{
	struct super_block *sb = file_inode(filp)->i_sb;

	if (!ns_capable(sb->s_user_ns, CAP_SYS_ADMIN))
		return -EPERM;

	/* If filesystem doesn't support freeze feature, return. */
	if (sb->s_op->freeze_fs == NULL && sb->s_op->freeze_super == NULL)
		return -EOPNOTSUPP;

	/* Freeze */
	if (sb->s_op->freeze_super)
		return sb->s_op->freeze_super(sb);
	return freeze_super(sb);
}