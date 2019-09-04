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
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  rtw_hal_enable_interrupt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_intf_start(_adapter *padapter)
{

	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("+pci_intf_start\n"));
	DBG_871X("+pci_intf_start\n");

#ifdef CONFIG_PCILED_BLINK
	rtw_led_control(padapter, LED_CTL_NO_LINK);
#endif
	//Enable hw interrupt
	rtw_hal_enable_interrupt(padapter);

	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("-pci_intf_start\n"));
	DBG_871X("-pci_intf_start\n");
}