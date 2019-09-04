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
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 unsigned int _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 
 int /*<<< orphan*/  rtw_read_port_cancel (int /*<<< orphan*/ ) ; 

unsigned int rtl8192cu_inirp_deinit(PADAPTER Adapter)
{	
	RT_TRACE(_module_hci_hal_init_c_,_drv_info_,("\n ===> usb_rx_deinit \n"));
	
	rtw_read_port_cancel(Adapter);

	RT_TRACE(_module_hci_hal_init_c_,_drv_info_,("\n <=== usb_rx_deinit \n"));

	return _SUCCESS;
}