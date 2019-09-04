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
typedef  int /*<<< orphan*/  dwc_thread_t ;
typedef  int /*<<< orphan*/  dwc_thread_function_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct task_struct* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,void*,char*) ; 

dwc_thread_t *DWC_THREAD_RUN(dwc_thread_function_t func, char *name, void *data)
{
	struct task_struct *thread = kthread_run(func, data, name);

	if (thread == ERR_PTR(-ENOMEM)) {
		return NULL;
	}

	return (dwc_thread_t *)thread;
}