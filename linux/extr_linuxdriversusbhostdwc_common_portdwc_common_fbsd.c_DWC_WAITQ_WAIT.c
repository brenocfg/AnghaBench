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
typedef  int int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ abort; } ;
typedef  TYPE_1__ dwc_waitq_t ;
typedef  int /*<<< orphan*/  (* dwc_waitq_condition_t ) (void*) ;

/* Variables and functions */
 int DWC_E_ABORT ; 
 int DWC_E_RESTART ; 
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  PCATCH ; 
 int msleep (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int32_t DWC_WAITQ_WAIT(dwc_waitq_t *wq, dwc_waitq_condition_t cond, void *data)
{
//	intrmask_t ipl;
	int result = 0;

	mtx_lock(&wq->lock);
//	ipl = splbio();

	/* Skip the sleep if already aborted or triggered */
	if (!wq->abort && !cond(data)) {
//		splx(ipl);
		result = msleep(wq, &wq->lock, PCATCH, "dw3wat", 0); // infinite timeout
//		ipl = splbio();
	}

	if (result == ERESTART) {	// signaled - restart
		result = -DWC_E_RESTART;

	} else if (result == EINTR) {	// signaled - interrupt
		result = -DWC_E_ABORT;

	} else if (wq->abort) {
		result = -DWC_E_ABORT;

	} else {
		result = 0;
	}

	wq->abort = 0;
//	splx(ipl);
	mtx_unlock(&wq->lock);
	return result;
}