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
struct kthread {scalar_t__ blkcg_css; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kfree (struct kthread*) ; 
 struct kthread* to_kthread (struct task_struct*) ; 

void free_kthread_struct(struct task_struct *k)
{
	struct kthread *kthread;

	/*
	 * Can be NULL if this kthread was created by kernel_thread()
	 * or if kmalloc() in kthread() failed.
	 */
	kthread = to_kthread(k);
#ifdef CONFIG_BLK_CGROUP
	WARN_ON_ONCE(kthread && kthread->blkcg_css);
#endif
	kfree(kthread);
}