#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ bup; scalar_t__ bSurpriseRemoved; int /*<<< orphan*/  (* intf_stop ) (TYPE_1__*) ;scalar_t__ bDriverStopped; scalar_t__ pnetdev; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  rtw_hal_deinit (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_stop_drv_threads (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void rtw_dev_unload(_adapter *padapter)
{
	struct net_device *pnetdev= (struct net_device*)padapter->pnetdev;

	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("+rtw_dev_unload\n"));

	if(padapter->bup == _TRUE)
	{
		DBG_871X("+rtw_dev_unload\n");

		padapter->bDriverStopped = _TRUE;
		#ifdef CONFIG_XMIT_ACK
		if (padapter->xmitpriv.ack_tx)
			rtw_ack_tx_done(&padapter->xmitpriv, RTW_SCTX_DONE_DRV_STOP);
		#endif

		//s3.
		if(padapter->intf_stop)
		{
			padapter->intf_stop(padapter);
		}

		//s4.
		rtw_stop_drv_threads(padapter);


		//s5.
		if(padapter->bSurpriseRemoved == _FALSE)
		{
			DBG_871X("r871x_dev_unload()->rtl871x_hal_deinit()\n");
			rtw_hal_deinit(padapter);

			padapter->bSurpriseRemoved = _TRUE;
		}

		padapter->bup = _FALSE;

	}
	else
	{
		RT_TRACE(_module_hci_intfs_c_,_drv_err_,("r871x_dev_unload():padapter->bup == _FALSE\n" ));
	}

	DBG_871X("-rtw_dev_unload\n");

	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("-rtw_dev_unload\n"));

}