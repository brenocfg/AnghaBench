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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int abort; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ dwc_waitq_t ;
typedef  scalar_t__ (* dwc_waitq_condition_t ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_E_ABORT ; 
 int /*<<< orphan*/  DWC_E_RESTART ; 
 int /*<<< orphan*/  DWC_E_UNKNOWN ; 
 int ERESTARTSYS ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int32_t DWC_WAITQ_WAIT(dwc_waitq_t *wq, dwc_waitq_condition_t cond, void *data)
{
	int result = wait_event_interruptible(wq->queue,
					      cond(data) || wq->abort);
	if (result == -ERESTARTSYS) {
		wq->abort = 0;
		return -DWC_E_RESTART;
	}

	if (wq->abort == 1) {
		wq->abort = 0;
		return -DWC_E_ABORT;
	}

	wq->abort = 0;

	if (result == 0) {
		return 0;
	}

	return -DWC_E_UNKNOWN;
}