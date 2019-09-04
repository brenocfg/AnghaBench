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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct dvobj_priv {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  disable_ht_for_spec_devid (struct pci_device_id const*) ; 
 int pci_alloc_irq (struct dvobj_priv*) ; 
 int /*<<< orphan*/  pci_dvobj_deinit (struct pci_dev*) ; 
 struct dvobj_priv* pci_dvobj_init (struct pci_dev*) ; 
 int rtw_drv_register_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_pci_if1_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtw_pci_if1_init (struct dvobj_priv*,struct pci_dev*,struct pci_device_id const*) ; 

__attribute__((used)) static int rtw_drv_init(struct pci_dev *pdev, const struct pci_device_id *did)
{
	int i, err = -ENODEV;

	int status;
	_adapter *if1 = NULL, *if2 = NULL;
	struct dvobj_priv *dvobj;

	RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("+rtw_drv_init\n"));

	//step 0.
	disable_ht_for_spec_devid(did);

	/* Initialize dvobj_priv */
	if ((dvobj = pci_dvobj_init(pdev)) == NULL) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("initialize device object priv Failed!\n"));
		goto exit;
	}

	/* Initialize if1 */
	if ((if1 = rtw_pci_if1_init(dvobj, pdev, did)) == NULL) {
		DBG_871X("rtw_pci_if1_init Failed!\n");
		goto free_dvobj;
	}

	/* Initialize if2 */
#ifdef CONFIG_CONCURRENT_MODE
	if((if2 = rtw_drv_if2_init(if1, pci_set_intf_ops)) == NULL) {
		goto free_if1;
	}
#endif

#ifdef CONFIG_GLOBAL_UI_PID
	if (ui_pid[1]!=0) {
		DBG_871X("ui_pid[1]:%d\n",ui_pid[1]);
		rtw_signal_process(ui_pid[1], SIGUSR2);
	}
#endif

	//dev_alloc_name && register_netdev
	if((status = rtw_drv_register_netdev(if1)) != _SUCCESS) {
		goto free_if1;
	}

#ifdef CONFIG_HOSTAPD_MLME
	hostapd_mode_init(if1);
#endif

#ifdef CONFIG_PLATFORM_RTD2880B
	DBG_871X("wlan link up\n");
	rtd2885_wlan_netlink_sendMsg("linkup", "8712");
#endif

#ifdef RTK_DMP_PLATFORM
	rtw_proc_init_one(if1->pnetdev);
#endif


	/* alloc irq */
	if (pci_alloc_irq(dvobj) != _SUCCESS)
		goto free_if2;

	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("-871x_drv - drv_init, success!\n"));
	//DBG_871X("-871x_drv - drv_init, success!\n");

	status = _SUCCESS;

free_if2:
	if(status != _SUCCESS && if2) {
		#ifdef CONFIG_CONCURRENT_MODE
		rtw_drv_if2_stop(if2);
		rtw_drv_if2_free(if2);
		#endif
	}
free_if1:
	if (status != _SUCCESS && if1) {
		rtw_pci_if1_deinit(if1);
	}
free_dvobj:
	if (status != _SUCCESS)
		pci_dvobj_deinit(pdev);
exit:
	return status == _SUCCESS?0:-ENODEV;
}