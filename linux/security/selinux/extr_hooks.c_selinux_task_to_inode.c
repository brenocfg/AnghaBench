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
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int dummy; } ;
struct inode_security_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  initialized; int /*<<< orphan*/  sid; int /*<<< orphan*/  sclass; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LABEL_INITIALIZED ; 
 int /*<<< orphan*/  inode_mode_to_security_class (int /*<<< orphan*/ ) ; 
 struct inode_security_struct* selinux_inode (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_sid (struct task_struct*) ; 

__attribute__((used)) static void selinux_task_to_inode(struct task_struct *p,
				  struct inode *inode)
{
	struct inode_security_struct *isec = selinux_inode(inode);
	u32 sid = task_sid(p);

	spin_lock(&isec->lock);
	isec->sclass = inode_mode_to_security_class(inode->i_mode);
	isec->sid = sid;
	isec->initialized = LABEL_INITIALIZED;
	spin_unlock(&isec->lock);
}