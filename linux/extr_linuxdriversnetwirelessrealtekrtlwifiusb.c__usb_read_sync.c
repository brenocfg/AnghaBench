#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct usb_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  usb_lock; } ;
struct TYPE_4__ {struct device* dev; } ;
struct rtl_priv {scalar_t__ usb_data_index; TYPE_1__ locks; int /*<<< orphan*/ * usb_data; TYPE_2__ io; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ REALTEK_USB_VENQT_CMD_IDX ; 
 int /*<<< orphan*/  REALTEK_USB_VENQT_CMD_REQ ; 
 scalar_t__ RTL_USB_MAX_RX_COUNT ; 
 int /*<<< orphan*/  _usbctrl_vendorreq_sync_read (struct usb_device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct usb_device* to_usb_device (struct device*) ; 

__attribute__((used)) static u32 _usb_read_sync(struct rtl_priv *rtlpriv, u32 addr, u16 len)
{
	struct device *dev = rtlpriv->io.dev;
	struct usb_device *udev = to_usb_device(dev);
	u8 request;
	u16 wvalue;
	u16 index;
	__le32 *data;
	unsigned long flags;

	spin_lock_irqsave(&rtlpriv->locks.usb_lock, flags);
	if (++rtlpriv->usb_data_index >= RTL_USB_MAX_RX_COUNT)
		rtlpriv->usb_data_index = 0;
	data = &rtlpriv->usb_data[rtlpriv->usb_data_index];
	spin_unlock_irqrestore(&rtlpriv->locks.usb_lock, flags);
	request = REALTEK_USB_VENQT_CMD_REQ;
	index = REALTEK_USB_VENQT_CMD_IDX; /* n/a */

	wvalue = (u16)addr;
	_usbctrl_vendorreq_sync_read(udev, request, wvalue, index, data, len);
	return le32_to_cpu(*data);
}