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
typedef  int int32_t ;
struct TYPE_3__ {int abort; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ dwc_waitq_t ;
typedef  scalar_t__ (* dwc_waitq_condition_t ) (void*) ;

/* Variables and functions */
 int DWC_E_ABORT ; 
 int DWC_E_RESTART ; 
 int DWC_E_TIMEOUT ; 
 int DWC_E_UNKNOWN ; 
 int ERESTARTSYS ; 
 int jiffies_to_msecs (int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int32_t DWC_WAITQ_WAIT_TIMEOUT(dwc_waitq_t *wq, dwc_waitq_condition_t cond,
			       void *data, int32_t msecs)
{
	int32_t tmsecs;
	int result = wait_event_interruptible_timeout(wq->queue,
						      cond(data) || wq->abort,
						      msecs_to_jiffies(msecs));
	if (result == -ERESTARTSYS) {
		wq->abort = 0;
		return -DWC_E_RESTART;
	}

	if (wq->abort == 1) {
		wq->abort = 0;
		return -DWC_E_ABORT;
	}

	wq->abort = 0;

	if (result > 0) {
		tmsecs = jiffies_to_msecs(result);
		if (!tmsecs) {
			return 1;
		}

		return tmsecs;
	}

	if (result == 0) {
		return -DWC_E_TIMEOUT;
	}

	return -DWC_E_UNKNOWN;
}