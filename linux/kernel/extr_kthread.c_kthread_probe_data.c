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
struct kthread {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  probe_kernel_read (void**,int /*<<< orphan*/ *,int) ; 
 struct kthread* to_kthread (struct task_struct*) ; 

void *kthread_probe_data(struct task_struct *task)
{
	struct kthread *kthread = to_kthread(task);
	void *data = NULL;

	probe_kernel_read(&data, &kthread->data, sizeof(data));
	return data;
}