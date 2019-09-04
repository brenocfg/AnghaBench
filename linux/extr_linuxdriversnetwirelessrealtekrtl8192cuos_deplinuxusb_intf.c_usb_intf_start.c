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
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  rtw_hal_inirp_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_intf_start(_adapter *padapter)
{
	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("+usb_intf_start\n"));
	rtw_hal_inirp_init(padapter);
	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("-usb_intf_start\n"));
}