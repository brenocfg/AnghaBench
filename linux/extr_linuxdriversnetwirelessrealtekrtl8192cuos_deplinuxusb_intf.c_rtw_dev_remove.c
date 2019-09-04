#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct dvobj_priv {scalar_t__ processing_dev_remove; TYPE_1__* if1; } ;
struct TYPE_7__ {scalar_t__ bSurpriseRemoved; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_8__ {scalar_t__ drv_registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  IPS_NONE ; 
 int /*<<< orphan*/  LeaveAllPowerSaveMode (TYPE_1__*) ; 
 int /*<<< orphan*/  PS_MODE_ACTIVE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  rtw_pm_set_ips (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_pm_set_lps (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_unregister_netdevs (struct dvobj_priv*) ; 
 int /*<<< orphan*/  rtw_usb_if1_deinit (TYPE_1__*) ; 
 TYPE_2__* usb_drv ; 
 int /*<<< orphan*/  usb_dvobj_deinit (struct usb_interface*) ; 
 struct dvobj_priv* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void rtw_dev_remove(struct usb_interface *pusb_intf)
{
	struct dvobj_priv *dvobj = usb_get_intfdata(pusb_intf);
	_adapter *padapter = dvobj->if1;

_func_exit_;

	DBG_871X("+rtw_dev_remove\n");
	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("+dev_remove()\n"));

	dvobj->processing_dev_remove = _TRUE;

	rtw_unregister_netdevs(dvobj);

	if(usb_drv->drv_registered == _TRUE)
	{
		//DBG_871X("r871xu_dev_remove():padapter->bSurpriseRemoved == _TRUE\n");
		padapter->bSurpriseRemoved = _TRUE;
	}
	/*else
	{
		//DBG_871X("r871xu_dev_remove():module removed\n");
		padapter->hw_init_completed = _FALSE;
	}*/

#if defined(CONFIG_HAS_EARLYSUSPEND) || defined(CONFIG_ANDROID_POWER)
	rtw_unregister_early_suspend(&padapter->pwrctrlpriv);
#endif

	rtw_pm_set_ips(padapter, IPS_NONE);
	rtw_pm_set_lps(padapter, PS_MODE_ACTIVE);

	LeaveAllPowerSaveMode(padapter);

#ifdef CONFIG_CONCURRENT_MODE
#ifdef CONFIG_MULTI_VIR_IFACES
	rtw_drv_stop_vir_ifaces(dvobj);
#endif //CONFIG_MULTI_VIR_IFACES
	rtw_drv_if2_stop(dvobj->if2);
#endif	//CONFIG_CONCURRENT_MODE

	rtw_usb_if1_deinit(padapter);

#ifdef CONFIG_CONCURRENT_MODE
#ifdef CONFIG_MULTI_VIR_IFACES
	rtw_drv_free_vir_ifaces(dvobj);
#endif //CONFIG_MULTI_VIR_IFACES
	rtw_drv_if2_free(dvobj->if2);
#endif //CONFIG_CONCURRENT_MODE

	usb_dvobj_deinit(pusb_intf);

	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("-dev_remove()\n"));
	DBG_871X("-r871xu_dev_remove, done\n");


#ifdef CONFIG_INTEL_PROXIM
	rtw_sw_export=NULL;
#endif

_func_exit_;

	return;

}