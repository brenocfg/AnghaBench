#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  terminate_cmdthread_comp; int /*<<< orphan*/  cmd_queue_comp; } ;
struct adapter {TYPE_1__ cmdpriv; scalar_t__ cmdThread; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

void rtw_stop_drv_threads(struct adapter *padapter)
{
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("+rtw_stop_drv_threads\n"));

	/* Below is to terminate rtw_cmd_thread & event_thread... */
	complete(&padapter->cmdpriv.cmd_queue_comp);
	if (padapter->cmdThread)
		wait_for_completion_interruptible(&padapter->cmdpriv.terminate_cmdthread_comp);
}