#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timex {scalar_t__ status; void* modes; scalar_t__ maxerror; } ;

/* Variables and functions */
 void* ADJ_MAXERROR ; 
 void* ADJ_STATUS ; 
 scalar_t__ STA_PLL ; 
 int adjtimex (struct timex*) ; 

int clear_time_state(void)
{
	struct timex tx;
	int ret;

	/*
	 * We have to call adjtime twice here, as kernels
	 * prior to 6b1859dba01c7 (included in 3.5 and
	 * -stable), had an issue with the state machine
	 * and wouldn't clear the STA_INS/DEL flag directly.
	 */
	tx.modes = ADJ_STATUS;
	tx.status = STA_PLL;
	ret = adjtimex(&tx);

	/* Clear maxerror, as it can cause UNSYNC to be set */
	tx.modes = ADJ_MAXERROR;
	tx.maxerror = 0;
	ret = adjtimex(&tx);

	/* Clear the status */
	tx.modes = ADJ_STATUS;
	tx.status = 0;
	ret = adjtimex(&tx);

	return ret;
}