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
struct task_struct {int dummy; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int S_ISGID ; 
 int S_ISUID ; 
 int /*<<< orphan*/  security_task_to_inode (struct task_struct*,struct inode*) ; 
 int /*<<< orphan*/  task_dump_owner (struct task_struct*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pid_update_inode(struct task_struct *task, struct inode *inode)
{
	task_dump_owner(task, inode->i_mode, &inode->i_uid, &inode->i_gid);

	inode->i_mode &= ~(S_ISUID | S_ISGID);
	security_task_to_inode(task, inode);
}