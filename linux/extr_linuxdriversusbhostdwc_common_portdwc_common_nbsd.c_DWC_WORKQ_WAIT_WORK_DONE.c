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
struct TYPE_4__ {int /*<<< orphan*/  waitq; } ;
typedef  TYPE_1__ dwc_workq_t ;

/* Variables and functions */
 int DWC_WAITQ_WAIT_TIMEOUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  work_done ; 

int DWC_WORKQ_WAIT_WORK_DONE(dwc_workq_t *workq, int timeout)
{
	return DWC_WAITQ_WAIT_TIMEOUT(workq->waitq, work_done, workq, timeout);
}