#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct dvobj_priv {int /*<<< orphan*/  processing_dev_remove; TYPE_1__* if1; } ;
struct TYPE_7__ {struct net_device* pnetdev; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  IPS_NONE ; 
 int /*<<< orphan*/  LeaveAllPowerSaveMode (TYPE_1__*) ; 
 int /*<<< orphan*/  PS_MODE_ACTIVE ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  pci_dvobj_deinit (struct pci_dev*) ; 
 struct dvobj_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtw_hal_disable_interrupt (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_pci_if1_deinit (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_pm_set_ips (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_pm_set_lps (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_unregister_netdevs (struct dvobj_priv*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rtw_dev_remove(struct pci_dev *pdev)
{
	struct dvobj_priv *pdvobjpriv = pci_get_drvdata(pdev);
	_adapter *padapter = pdvobjpriv->if1;
	struct net_device *pnetdev = padapter->pnetdev;

_func_exit_;

	DBG_871X("+rtw_dev_remove\n");

	pdvobjpriv->processing_dev_remove = _TRUE;

	if (unlikely(!padapter)) {
		return;
	}

	rtw_unregister_netdevs(pdvobjpriv);

	#if 0
#ifdef RTK_DMP_PLATFORM
	padapter->bSurpriseRemoved = _FALSE;	// always trate as device exists
											// this will let the driver to disable it's interrupt
#else
	if(pci_drvpriv.drv_registered == _TRUE)
	{
		//DBG_871X("r871xu_dev_remove():padapter->bSurpriseRemoved == _TRUE\n");
		padapter->bSurpriseRemoved = _TRUE;
	}
	/*else
	{
		//DBG_871X("r871xu_dev_remove():module removed\n");
		padapter->hw_init_completed = _FALSE;
	}*/
#endif
	#endif

#if defined(CONFIG_HAS_EARLYSUSPEND) || defined(CONFIG_ANDROID_POWER)
	rtw_unregister_early_suspend(&padapter->pwrctrlpriv);
#endif

	rtw_pm_set_ips(padapter, IPS_NONE);
	rtw_pm_set_lps(padapter, PS_MODE_ACTIVE);

	LeaveAllPowerSaveMode(padapter);

	rtw_hal_disable_interrupt(padapter);

#ifdef CONFIG_CONCURRENT_MODE
	rtw_drv_if2_stop(pdvobjpriv->if2);
#endif //CONFIG_CONCURRENT_MODE

	rtw_pci_if1_deinit(padapter);

#ifdef CONFIG_CONCURRENT_MODE
	rtw_drv_if2_free(pdvobjpriv->if2);
#endif

	pci_dvobj_deinit(pdev);

	DBG_871X("-r871xu_dev_remove, done\n");

_func_exit_;
	return;
}