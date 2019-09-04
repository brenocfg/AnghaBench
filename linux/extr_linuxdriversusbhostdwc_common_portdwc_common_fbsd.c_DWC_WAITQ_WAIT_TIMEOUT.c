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
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ abort; } ;
typedef  TYPE_1__ dwc_waitq_t ;
typedef  int /*<<< orphan*/  (* dwc_waitq_condition_t ) (void*) ;

/* Variables and functions */
 int DWC_E_ABORT ; 
 int DWC_E_RESTART ; 
 int DWC_E_TIMEOUT ; 
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  PCATCH ; 
 int /*<<< orphan*/  getmicrouptime (struct timeval*) ; 
 int msleep (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

int32_t DWC_WAITQ_WAIT_TIMEOUT(dwc_waitq_t *wq, dwc_waitq_condition_t cond,
			       void *data, int32_t msecs)
{
	struct timeval tv, tv1, tv2;
//	intrmask_t ipl;
	int result = 0;

	tv.tv_sec = msecs / 1000;
	tv.tv_usec = (msecs - tv.tv_sec * 1000) * 1000;

	mtx_lock(&wq->lock);
//	ipl = splbio();

	/* Skip the sleep if already aborted or triggered */
	if (!wq->abort && !cond(data)) {
//		splx(ipl);
		getmicrouptime(&tv1);
		result = msleep(wq, &wq->lock, PCATCH, "dw3wto", tvtohz(&tv));
		getmicrouptime(&tv2);
//		ipl = splbio();
	}

	if (result == 0) {			// awoken
		if (wq->abort) {
			result = -DWC_E_ABORT;
		} else {
			tv2.tv_usec -= tv1.tv_usec;
			if (tv2.tv_usec < 0) {
				tv2.tv_usec += 1000000;
				tv2.tv_sec--;
			}

			tv2.tv_sec -= tv1.tv_sec;
			result = tv2.tv_sec * 1000 + tv2.tv_usec / 1000;
			result = msecs - result;
			if (result <= 0)
				result = 1;
		}
	} else if (result == ERESTART) {	// signaled - restart
		result = -DWC_E_RESTART;

	} else if (result == EINTR) {		// signaled - interrupt
		result = -DWC_E_ABORT;

	} else {				// timed out
		result = -DWC_E_TIMEOUT;
	}

	wq->abort = 0;
//	splx(ipl);
	mtx_unlock(&wq->lock);
	return result;
}