#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bInternalAutoSuspend; } ;
struct TYPE_4__ {scalar_t__ ack_tx; } ;
struct adapter {int bup; int bDriverStopped; int bSurpriseRemoved; TYPE_1__ pwrctrlpriv; TYPE_2__ xmitpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_SCTX_DONE_DRV_STOP ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rtw_ack_tx_done (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hal_deinit (struct adapter*) ; 
 int /*<<< orphan*/  rtw_stop_drv_threads (struct adapter*) ; 
 int /*<<< orphan*/  usb_intf_stop (struct adapter*) ; 

__attribute__((used)) static void rtw_dev_unload(struct adapter *padapter)
{
	RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("+rtw_dev_unload\n"));

	if (padapter->bup) {
		pr_debug("===> rtw_dev_unload\n");
		padapter->bDriverStopped = true;
		if (padapter->xmitpriv.ack_tx)
			rtw_ack_tx_done(&padapter->xmitpriv, RTW_SCTX_DONE_DRV_STOP);
		/* s3. */
		usb_intf_stop(padapter);
		/* s4. */
		if (!padapter->pwrctrlpriv.bInternalAutoSuspend)
			rtw_stop_drv_threads(padapter);

		/* s5. */
		if (!padapter->bSurpriseRemoved) {
			rtw_hal_deinit(padapter);
			padapter->bSurpriseRemoved = true;
		}

		padapter->bup = false;
	} else {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_,
			 ("r871x_dev_unload():padapter->bup == false\n"));
	}

	pr_debug("<=== rtw_dev_unload\n");

	RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("-rtw_dev_unload\n"));
}