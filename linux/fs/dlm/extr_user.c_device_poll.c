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
struct file {struct dlm_user_proc* private_data; } ;
struct dlm_user_proc {int /*<<< orphan*/  asts_spin; int /*<<< orphan*/  asts; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t device_poll(struct file *file, poll_table *wait)
{
	struct dlm_user_proc *proc = file->private_data;

	poll_wait(file, &proc->wait, wait);

	spin_lock(&proc->asts_spin);
	if (!list_empty(&proc->asts)) {
		spin_unlock(&proc->asts_spin);
		return EPOLLIN | EPOLLRDNORM;
	}
	spin_unlock(&proc->asts_spin);
	return 0;
}