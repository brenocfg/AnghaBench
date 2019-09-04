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
typedef  int /*<<< orphan*/  u8 ;
struct intf_priv {scalar_t__ max_iosz; scalar_t__ allocated_io_rwmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,scalar_t__) ; 

void usb_unload_intf_priv(struct intf_priv *pintfpriv)
{

_func_enter_;
	
	RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n+usb_unload_intf_priv\n"));
	
	rtw_mfree((u8 *)(pintfpriv->allocated_io_rwmem), pintfpriv->max_iosz+4);
	
#ifdef PLATFORM_WINDOWS
	if(pintfpriv->piorw_urb)
		ExFreePool(pintfpriv->piorw_urb);	

	if(pintfpriv->piorw_irp)
		IoFreeIrp(pintfpriv->piorw_irp);
#endif		


#ifdef PLATFORM_LINUX
	RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\npintfpriv->io_irp_cnt=%d\n",pintfpriv->io_irp_cnt));
	pintfpriv->io_irp_cnt--;
	if(pintfpriv->io_irp_cnt){
		if(pintfpriv->bio_irp_pending==_TRUE){
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\nkill iorw_urb\n"));
		usb_kill_urb(pintfpriv->piorw_urb);
		}
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n wait io_retevt\n"));
		_rtw_down_sema(&(pintfpriv->io_retevt));
	}
	RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n cancel io_urb ok\n"));
#endif

	RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n-usb_unload_intf_priv\n"));

_func_exit_;
	
}