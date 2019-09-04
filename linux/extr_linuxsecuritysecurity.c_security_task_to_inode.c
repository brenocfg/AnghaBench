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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_void_hook (int /*<<< orphan*/ ,struct task_struct*,struct inode*) ; 
 int /*<<< orphan*/  task_to_inode ; 

void security_task_to_inode(struct task_struct *p, struct inode *inode)
{
	call_void_hook(task_to_inode, p, inode);
}