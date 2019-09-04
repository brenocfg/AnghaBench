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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  rtw_stop_cmd_thread (int /*<<< orphan*/ *) ; 

void rtw_stop_drv_threads (_adapter *padapter)
{
	RT_TRACE(_module_os_intfs_c_,_drv_info_,("+rtw_stop_drv_threads\n"));

#ifdef CONFIG_CONCURRENT_MODE
	if(padapter->isprimary == _TRUE)
#endif //CONFIG_CONCURRENT_MODE
	{
		rtw_stop_cmd_thread(padapter);
	}

#ifdef CONFIG_EVENT_THREAD_MODE
        _rtw_up_sema(&padapter->evtpriv.evt_notify);
	if(padapter->evtThread){
		_rtw_down_sema(&padapter->evtpriv.terminate_evtthread_sema);
	}
#endif

#ifdef CONFIG_XMIT_THREAD_MODE
	// Below is to termindate tx_thread...
	_rtw_up_sema(&padapter->xmitpriv.xmit_sema);
	_rtw_down_sema(&padapter->xmitpriv.terminate_xmitthread_sema);
	RT_TRACE(_module_os_intfs_c_,_drv_info_,("\n drv_halt: rtw_xmit_thread can be terminated ! \n"));
#endif

#ifdef CONFIG_RECV_THREAD_MODE
	// Below is to termindate rx_thread...
	_rtw_up_sema(&padapter->recvpriv.recv_sema);
	_rtw_down_sema(&padapter->recvpriv.terminate_recvthread_sema);
	RT_TRACE(_module_os_intfs_c_,_drv_info_,("\n drv_halt:recv_thread can be terminated! \n"));
#endif


}