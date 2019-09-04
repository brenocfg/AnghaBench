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
struct TYPE_4__ {scalar_t__ abort; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ dwc_waitq_t ;

/* Variables and functions */
 TYPE_1__* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

dwc_waitq_t *DWC_WAITQ_ALLOC(void)
{
	dwc_waitq_t *wq = DWC_ALLOC(sizeof(*wq));

	if (!wq) {
		DWC_ERROR("Cannot allocate memory for waitqueue\n");
		return NULL;
	}

	init_waitqueue_head(&wq->queue);
	wq->abort = 0;
	return wq;
}