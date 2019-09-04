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
struct adapter {int /*<<< orphan*/  bSurpriseRemoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  rtw_hal_inirp_deinit (struct adapter*) ; 
 int /*<<< orphan*/  usb_write_port_cancel (struct adapter*) ; 

void usb_intf_stop(struct adapter *padapter)
{
	RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("+usb_intf_stop\n"));

	/* disable_hw_interrupt */
	if (!padapter->bSurpriseRemoved) {
		/* device still exists, so driver can do i/o operation */
		/* TODO: */
		RT_TRACE(_module_hci_intfs_c_, _drv_err_,
			 ("SurpriseRemoved == false\n"));
	}

	/* cancel in irp */
	rtw_hal_inirp_deinit(padapter);

	/* cancel out irp */
	usb_write_port_cancel(padapter);

	/* todo:cancel other irps */

	RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("-usb_intf_stop\n"));
}