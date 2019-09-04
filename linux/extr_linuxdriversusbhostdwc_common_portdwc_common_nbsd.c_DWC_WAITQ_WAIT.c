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
 int ERESTART ; 
 int /*<<< orphan*/  PCATCH ; 
 int ltsleep (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int splbio () ; 
 int /*<<< orphan*/  splx (int) ; 

int32_t DWC_WAITQ_WAIT(dwc_waitq_t *wq, dwc_waitq_condition_t cond, void *data)
{
	int ipl;
	int result = 0;

	simple_lock(&wq->lock);
	ipl = splbio();

	/* Skip the sleep if already aborted or triggered */
	if (!wq->abort && !cond(data)) {
		splx(ipl);
		result = ltsleep(wq, PCATCH, "dw3wat", 0, &wq->lock); // infinite timeout
		ipl = splbio();
	}

	if (result == 0) {			// awoken
		if (wq->abort) {
			wq->abort = 0;
			result = -DWC_E_ABORT;
		} else {
			result = 0;
		}

		splx(ipl);
		simple_unlock(&wq->lock);
	} else {
		wq->abort = 0;
		splx(ipl);
		simple_unlock(&wq->lock);

		if (result == ERESTART) {	// signaled - restart
			result = -DWC_E_RESTART;
		} else {			// signaled - must be EINTR
			result = -DWC_E_ABORT;
		}
	}

	return result;
}