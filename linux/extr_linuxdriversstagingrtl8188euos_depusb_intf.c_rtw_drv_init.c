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
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct dvobj_priv {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct adapter* rtw_usb_if1_init (struct dvobj_priv*,struct usb_interface*,struct usb_device_id const*) ; 
 int /*<<< orphan*/  usb_dvobj_deinit (struct usb_interface*) ; 
 struct dvobj_priv* usb_dvobj_init (struct usb_interface*) ; 

__attribute__((used)) static int rtw_drv_init(struct usb_interface *pusb_intf, const struct usb_device_id *pdid)
{
	struct adapter *if1 = NULL;
	struct dvobj_priv *dvobj;

	/* Initialize dvobj_priv */
	dvobj = usb_dvobj_init(pusb_intf);
	if (!dvobj) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_,
			 ("initialize device object priv Failed!\n"));
		goto exit;
	}

	if1 = rtw_usb_if1_init(dvobj, pusb_intf, pdid);
	if (!if1) {
		pr_debug("rtw_init_primarystruct adapter Failed!\n");
		goto free_dvobj;
	}

	return 0;

free_dvobj:
	usb_dvobj_deinit(pusb_intf);
exit:
	return -ENODEV;
}