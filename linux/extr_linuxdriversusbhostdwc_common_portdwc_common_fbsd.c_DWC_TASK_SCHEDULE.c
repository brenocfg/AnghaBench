#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  t; } ;
typedef  TYPE_1__ dwc_tasklet_t ;

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_enqueue_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_fast ; 

void DWC_TASK_SCHEDULE(dwc_tasklet_t *task)
{
	/* Uses predefined system queue */
	taskqueue_enqueue_fast(taskqueue_fast, &task->t);
}