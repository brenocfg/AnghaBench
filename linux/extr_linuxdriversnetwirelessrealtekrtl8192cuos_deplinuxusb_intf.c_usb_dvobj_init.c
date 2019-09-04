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
struct usb_interface_descriptor {int bNumEndpoints; int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct usb_host_interface {struct usb_host_endpoint* endpoint; struct usb_interface_descriptor desc; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct usb_host_endpoint {struct usb_endpoint_descriptor desc; } ;
struct usb_config_descriptor {int /*<<< orphan*/  bNumInterfaces; } ;
struct usb_host_config {struct usb_config_descriptor desc; } ;
struct usb_device_descriptor {int dummy; } ;
struct usb_device {scalar_t__ speed; struct usb_host_config* actconfig; struct usb_device_descriptor descriptor; } ;
struct dvobj_priv {int nr_endpoint; int /*<<< orphan*/  usb_suspend_sema; int /*<<< orphan*/  ishighspeed; scalar_t__ RtNumOutPipes; int /*<<< orphan*/  RtNumInPipes; int /*<<< orphan*/ * ep_num; int /*<<< orphan*/  InterfaceNumber; int /*<<< orphan*/  NumInterfaces; struct usb_device* pusbdev; struct usb_interface* pusbintf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RT_usb_endpoint_is_bulk_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ RT_usb_endpoint_is_bulk_out (struct usb_endpoint_descriptor*) ; 
 scalar_t__ RT_usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  RT_usb_endpoint_num (struct usb_endpoint_descriptor*) ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int _FAIL ; 
 int /*<<< orphan*/  _FALSE ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  _rtw_init_sema (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devobj_deinit (struct dvobj_priv*) ; 
 struct dvobj_priv* devobj_init () ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int rtw_init_intf_priv (struct dvobj_priv*) ; 
 int /*<<< orphan*/  rtw_reset_continual_urb_error (struct dvobj_priv*) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct dvobj_priv*) ; 

__attribute__((used)) static struct dvobj_priv *usb_dvobj_init(struct usb_interface *usb_intf)
{
	int	i;
	u8	val8;
	int	status = _FAIL;
	struct dvobj_priv *pdvobjpriv = NULL;
	struct usb_device				*pusbd;
	struct usb_device_descriptor 	*pdev_desc;
	struct usb_host_config			*phost_conf;
	struct usb_config_descriptor		*pconf_desc;
	struct usb_host_interface		*phost_iface;
	struct usb_interface_descriptor	*piface_desc;
	struct usb_host_endpoint		*phost_endp;
	struct usb_endpoint_descriptor	*pendp_desc;

_func_enter_;

	if((pdvobjpriv = devobj_init()) == NULL) {
		goto exit;
	}

	pdvobjpriv->pusbintf = usb_intf ;
	pusbd = pdvobjpriv->pusbdev = interface_to_usbdev(usb_intf);
	usb_set_intfdata(usb_intf, pdvobjpriv);

	pdvobjpriv->RtNumInPipes = 0;
	pdvobjpriv->RtNumOutPipes = 0;


	pdev_desc = &pusbd->descriptor;
#if 0
	DBG_871X("\n8712_usb_device_descriptor:\n");
	DBG_871X("bLength=%x\n", pdev_desc->bLength);
	DBG_871X("bDescriptorType=%x\n", pdev_desc->bDescriptorType);
	DBG_871X("bcdUSB=%x\n", pdev_desc->bcdUSB);
	DBG_871X("bDeviceClass=%x\n", pdev_desc->bDeviceClass);
	DBG_871X("bDeviceSubClass=%x\n", pdev_desc->bDeviceSubClass);
	DBG_871X("bDeviceProtocol=%x\n", pdev_desc->bDeviceProtocol);
	DBG_871X("bMaxPacketSize0=%x\n", pdev_desc->bMaxPacketSize0);
	DBG_871X("idVendor=%x\n", pdev_desc->idVendor);
	DBG_871X("idProduct=%x\n", pdev_desc->idProduct);
	DBG_871X("bcdDevice=%x\n", pdev_desc->bcdDevice);
	DBG_871X("iManufacturer=%x\n", pdev_desc->iManufacturer);
	DBG_871X("iProduct=%x\n", pdev_desc->iProduct);
	DBG_871X("iSerialNumber=%x\n", pdev_desc->iSerialNumber);
	DBG_871X("bNumConfigurations=%x\n", pdev_desc->bNumConfigurations);
#endif

	phost_conf = pusbd->actconfig;
	pconf_desc = &phost_conf->desc;

#if 0
	DBG_871X("\n8712_usb_configuration_descriptor:\n");
	DBG_871X("bLength=%x\n", pconf_desc->bLength);
	DBG_871X("bDescriptorType=%x\n", pconf_desc->bDescriptorType);
	DBG_871X("wTotalLength=%x\n", pconf_desc->wTotalLength);
	DBG_871X("bNumInterfaces=%x\n", pconf_desc->bNumInterfaces);
	DBG_871X("bConfigurationValue=%x\n", pconf_desc->bConfigurationValue);
	DBG_871X("iConfiguration=%x\n", pconf_desc->iConfiguration);
	DBG_871X("bmAttributes=%x\n", pconf_desc->bmAttributes);
	DBG_871X("bMaxPower=%x\n", pconf_desc->bMaxPower);
#endif

	//DBG_871X("\n/****** num of altsetting = (%d) ******/\n", usb_intf->num_altsetting);

	phost_iface = &usb_intf->altsetting[0];
	piface_desc = &phost_iface->desc;

#if 0
	DBG_871X("\n8712_usb_interface_descriptor:\n");
	DBG_871X("bLength=%x\n", piface_desc->bLength);
	DBG_871X("bDescriptorType=%x\n", piface_desc->bDescriptorType);
	DBG_871X("bInterfaceNumber=%x\n", piface_desc->bInterfaceNumber);
	DBG_871X("bAlternateSetting=%x\n", piface_desc->bAlternateSetting);
	DBG_871X("bNumEndpoints=%x\n", piface_desc->bNumEndpoints);
	DBG_871X("bInterfaceClass=%x\n", piface_desc->bInterfaceClass);
	DBG_871X("bInterfaceSubClass=%x\n", piface_desc->bInterfaceSubClass);
	DBG_871X("bInterfaceProtocol=%x\n", piface_desc->bInterfaceProtocol);
	DBG_871X("iInterface=%x\n", piface_desc->iInterface);
#endif

	pdvobjpriv->NumInterfaces = pconf_desc->bNumInterfaces;
	pdvobjpriv->InterfaceNumber = piface_desc->bInterfaceNumber;
	pdvobjpriv->nr_endpoint = piface_desc->bNumEndpoints;

	//DBG_871X("\ndump usb_endpoint_descriptor:\n");

	for (i = 0; i < pdvobjpriv->nr_endpoint; i++)
	{
		phost_endp = phost_iface->endpoint + i;
		if (phost_endp)
		{
			pendp_desc = &phost_endp->desc;

			DBG_871X("\nusb_endpoint_descriptor(%d):\n", i);
			DBG_871X("bLength=%x\n",pendp_desc->bLength);
			DBG_871X("bDescriptorType=%x\n",pendp_desc->bDescriptorType);
			DBG_871X("bEndpointAddress=%x\n",pendp_desc->bEndpointAddress);
			//DBG_871X("bmAttributes=%x\n",pendp_desc->bmAttributes);
			//DBG_871X("wMaxPacketSize=%x\n",pendp_desc->wMaxPacketSize);
			DBG_871X("wMaxPacketSize=%x\n",le16_to_cpu(pendp_desc->wMaxPacketSize));
			DBG_871X("bInterval=%x\n",pendp_desc->bInterval);
			//DBG_871X("bRefresh=%x\n",pendp_desc->bRefresh);
			//DBG_871X("bSynchAddress=%x\n",pendp_desc->bSynchAddress);

			if (RT_usb_endpoint_is_bulk_in(pendp_desc))
			{
				DBG_871X("RT_usb_endpoint_is_bulk_in = %x\n", RT_usb_endpoint_num(pendp_desc));
				pdvobjpriv->RtNumInPipes++;
			}
			else if (RT_usb_endpoint_is_int_in(pendp_desc))
			{
				DBG_871X("RT_usb_endpoint_is_int_in = %x, Interval = %x\n", RT_usb_endpoint_num(pendp_desc),pendp_desc->bInterval);
				pdvobjpriv->RtNumInPipes++;
			}
			else if (RT_usb_endpoint_is_bulk_out(pendp_desc))
			{
				DBG_871X("RT_usb_endpoint_is_bulk_out = %x\n", RT_usb_endpoint_num(pendp_desc));
				pdvobjpriv->RtNumOutPipes++;
			}
			pdvobjpriv->ep_num[i] = RT_usb_endpoint_num(pendp_desc);
		}
	}

	DBG_871X("nr_endpoint=%d, in_num=%d, out_num=%d\n\n", pdvobjpriv->nr_endpoint, pdvobjpriv->RtNumInPipes, pdvobjpriv->RtNumOutPipes);

	if (pusbd->speed == USB_SPEED_HIGH) {
		pdvobjpriv->ishighspeed = _TRUE;
		DBG_871X("USB_SPEED_HIGH\n");
	} else {
		pdvobjpriv->ishighspeed = _FALSE;
		DBG_871X("NON USB_SPEED_HIGH\n");
	}

	if (rtw_init_intf_priv(pdvobjpriv) == _FAIL) {
		RT_TRACE(_module_os_intfs_c_,_drv_err_,("\n Can't INIT rtw_init_intf_priv\n"));
		goto free_dvobj;
	}

	//.3 misc
	_rtw_init_sema(&(pdvobjpriv->usb_suspend_sema), 0);

	rtw_reset_continual_urb_error(pdvobjpriv);

	usb_get_dev(pusbd);

	//DBG_871X("%s %d\n", __func__, ATOMIC_READ(&usb_intf->dev.kobj.kref.refcount));

	status = _SUCCESS;

free_dvobj:
	if (status != _SUCCESS && pdvobjpriv) {
		usb_set_intfdata(usb_intf, NULL);
		devobj_deinit(pdvobjpriv);
		pdvobjpriv = NULL;
	}
exit:
_func_exit_;
	return pdvobjpriv;
}