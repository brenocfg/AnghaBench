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
struct TYPE_2__ {int /*<<< orphan*/  terminate_xmitthread_sema; int /*<<< orphan*/  xmit_sema; } ;
struct adapter {TYPE_1__ xmitpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_hal_stop_thread (struct adapter*) ; 
 int /*<<< orphan*/  rtw_stop_cmd_thread (struct adapter*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void rtw_stop_drv_threads (struct adapter *padapter)
{
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("+rtw_stop_drv_threads\n"));

	rtw_stop_cmd_thread(padapter);

	/*  Below is to termindate tx_thread... */
	up(&padapter->xmitpriv.xmit_sema);
	down(&padapter->xmitpriv.terminate_xmitthread_sema);
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("\n drv_halt: rtw_xmit_thread can be terminated !\n"));

	rtw_hal_stop_thread(padapter);
}