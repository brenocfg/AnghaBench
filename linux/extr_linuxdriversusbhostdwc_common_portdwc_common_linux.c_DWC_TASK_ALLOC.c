#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  t; void* data; int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ dwc_tasklet_t ;
typedef  int /*<<< orphan*/  dwc_tasklet_callback_t ;

/* Variables and functions */
 TYPE_1__* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  tasklet_callback ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

dwc_tasklet_t *DWC_TASK_ALLOC(char *name, dwc_tasklet_callback_t cb, void *data)
{
	dwc_tasklet_t *t = DWC_ALLOC(sizeof(*t));

	if (t) {
		t->cb = cb;
		t->data = data;
		tasklet_init(&t->t, tasklet_callback, (unsigned long)t);
	} else {
		DWC_ERROR("Cannot allocate memory for tasklet\n");
	}

	return t;
}