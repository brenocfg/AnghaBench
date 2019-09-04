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
typedef  scalar_t__ uint ;
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct dvobj_priv {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  process_spec_devid (struct usb_device_id const*) ; 
 scalar_t__ rtw_drv_register_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_usb_if1_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtw_usb_if1_init (struct dvobj_priv*,struct usb_interface*,struct usb_device_id const*) ; 
 int /*<<< orphan*/  usb_dvobj_deinit (struct usb_interface*) ; 
 struct dvobj_priv* usb_dvobj_init (struct usb_interface*) ; 

__attribute__((used)) static int rtw_drv_init(struct usb_interface *pusb_intf, const struct usb_device_id *did)
{
	int i;
	uint status = _FAIL;
	_adapter *if1 = NULL, *if2 = NULL;
	struct dvobj_priv *dvobj = NULL;


	RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("+rtw_drv_init\n"));


	//step 0.
	process_spec_devid(did);

	/* Initialize dvobj_priv */
	if ((dvobj = usb_dvobj_init(pusb_intf)) == NULL) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("initialize device object priv Failed!\n"));
		goto exit;
	}

	/* Initialize if1 */
	if ((if1 = rtw_usb_if1_init(dvobj, pusb_intf, did)) == NULL) {
		DBG_871X("rtw_usb_if1_init Failed!\n");
		goto free_dvobj;
	}

	/* Initialize if2 */
#ifdef CONFIG_CONCURRENT_MODE
	if((if2 = rtw_drv_if2_init(if1, usb_set_intf_ops)) == NULL) {
		goto free_if1;
	}
#ifdef CONFIG_MULTI_VIR_IFACES
	for(i=0; i<if1->registrypriv.ext_iface_num;i++)
	{
		if(rtw_drv_add_vir_if(if1, usb_set_intf_ops) == NULL)
		{
			DBG_871X("rtw_drv_add_iface failed! (%d)\n", i);
			goto free_if1;
		}
	}
#endif //CONFIG_MULTI_VIR_IFACES
#endif

#ifdef CONFIG_INTEL_PROXIM
	rtw_sw_export=if1;
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

	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("-871x_drv - drv_init, success!\n"));

	status = _SUCCESS;

free_if1:
	if (status != _SUCCESS && if1) {
		rtw_usb_if1_deinit(if1);
	}
free_dvobj:
	if (status != _SUCCESS)
		usb_dvobj_deinit(pusb_intf);
exit:
	return status == _SUCCESS?0:-ENODEV;
}