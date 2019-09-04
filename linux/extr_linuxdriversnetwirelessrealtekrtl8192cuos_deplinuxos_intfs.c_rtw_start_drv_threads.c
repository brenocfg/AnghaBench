#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  terminate_cmdthread_sema; } ;
struct TYPE_6__ {TYPE_1__ cmdpriv; int /*<<< orphan*/  cmdThread; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  _rtw_down_sema (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  rtw_cmd_thread ; 

u32 rtw_start_drv_threads(_adapter *padapter)
{

	u32 _status = _SUCCESS;

	RT_TRACE(_module_os_intfs_c_,_drv_info_,("+rtw_start_drv_threads\n"));
#ifdef CONFIG_XMIT_THREAD_MODE
	padapter->xmitThread = kthread_run(rtw_xmit_thread, padapter, "RTW_XMIT_THREAD");
	if(IS_ERR(padapter->xmitThread))
		_status = _FAIL;
#endif

#ifdef CONFIG_RECV_THREAD_MODE
	padapter->recvThread = kthread_run(rtw_recv_thread, padapter, "RTW_RECV_THREAD");
	if(IS_ERR(padapter->recvThread))
		_status = _FAIL;
#endif

#ifdef CONFIG_CONCURRENT_MODE
	if(padapter->isprimary == _TRUE)
#endif //CONFIG_CONCURRENT_MODE
	{
		padapter->cmdThread = kthread_run(rtw_cmd_thread, padapter, "RTW_CMD_THREAD");
		if(IS_ERR(padapter->cmdThread))
			_status = _FAIL;
		else
			_rtw_down_sema(&padapter->cmdpriv.terminate_cmdthread_sema); //wait for cmd_thread to run
	}


#ifdef CONFIG_EVENT_THREAD_MODE
	padapter->evtThread = kthread_run(event_thread, padapter, "RTW_EVENT_THREAD");
	if(IS_ERR(padapter->evtThread))
		_status = _FAIL;
#endif

	return _status;

}