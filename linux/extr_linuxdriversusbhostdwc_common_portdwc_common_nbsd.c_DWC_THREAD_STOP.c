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
struct TYPE_3__ {int abort; } ;
typedef  TYPE_1__ dwc_thread_t ;

/* Variables and functions */
 int DWC_E_TIMEOUT ; 
 int DWC_E_UNKNOWN ; 
 int EWOULDBLOCK ; 
 int hz ; 
 int tsleep (int*,int /*<<< orphan*/ ,char*,int) ; 

int DWC_THREAD_STOP(dwc_thread_t *thread)
{
	int retval;

	thread->abort = 1;
	retval = tsleep(&thread->abort, 0, "dw3stp", 60 * hz);

	if (retval == 0) {
		/* DWC_THREAD_EXIT() will free the thread struct */
		return 0;
	}

	/* NOTE: We leak the thread struct if thread doesn't die */

	if (retval == EWOULDBLOCK) {
		return -DWC_E_TIMEOUT;
	}

	return -DWC_E_UNKNOWN;
}