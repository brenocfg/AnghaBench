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
struct TYPE_5__ {int /*<<< orphan*/  t; void* data; int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ dwc_tasklet_t ;
typedef  int /*<<< orphan*/  dwc_tasklet_callback_t ;

/* Variables and functions */
 TYPE_1__* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  tasklet_callback ; 

dwc_tasklet_t *DWC_TASK_ALLOC(char *name, dwc_tasklet_callback_t cb, void *data)
{
	dwc_tasklet_t *task = DWC_ALLOC(sizeof(*task));

	if (task) {
		task->cb = cb;
		task->data = data;
		TASK_INIT(&task->t, 0, tasklet_callback, task);
	} else {
		DWC_ERROR("Cannot allocate memory for tasklet");
	}

	return task;
}