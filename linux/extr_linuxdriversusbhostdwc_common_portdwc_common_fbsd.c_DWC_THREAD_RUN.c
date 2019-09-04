#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  proc; scalar_t__ abort; } ;
typedef  TYPE_1__ dwc_thread_t ;
typedef  scalar_t__ dwc_thread_function_t ;

/* Variables and functions */
 TYPE_1__* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int RFNOWAIT ; 
 int RFPROC ; 
 int kthread_create (void (*) (void*),void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char*) ; 

dwc_thread_t *DWC_THREAD_RUN(dwc_thread_function_t func, char *name, void *data)
{
	int retval;
	dwc_thread_t *thread = DWC_ALLOC(sizeof(*thread));

	if (!thread) {
		return NULL;
	}

	thread->abort = 0;
	retval = kthread_create((void (*)(void *))func, data, &thread->proc,
				RFPROC | RFNOWAIT, 0, "%s", name);
	if (retval) {
		DWC_FREE(thread);
		return NULL;
	}

	return thread;
}