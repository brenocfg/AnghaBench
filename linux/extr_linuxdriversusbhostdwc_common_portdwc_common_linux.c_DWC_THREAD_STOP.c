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

/* Variables and functions */
 int kthread_stop (struct task_struct*) ; 

int DWC_THREAD_STOP(dwc_thread_t *thread)
{
	return kthread_stop((struct task_struct *)thread);
}