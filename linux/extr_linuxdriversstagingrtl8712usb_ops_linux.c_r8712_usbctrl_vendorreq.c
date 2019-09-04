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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct usb_device {int dummy; } ;
struct intf_priv {scalar_t__ intf_dev; } ;
struct dvobj_priv {struct usb_device* pusbdev; } ;
typedef  scalar_t__ palloc_buf ;
typedef  int addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int RTL871X_VENQT_READ ; 
 int RTL871X_VENQT_WRITE ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 int usb_control_msg (struct usb_device*,unsigned int,int,int,scalar_t__,scalar_t__,int*,scalar_t__,int) ; 
 unsigned int usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int r8712_usbctrl_vendorreq(struct intf_priv *pintfpriv, u8 request, u16 value,
		      u16 index, void *pdata, u16 len, u8 requesttype)
{
	unsigned int pipe;
	int status;
	u8 reqtype;
	struct dvobj_priv *pdvobjpriv = (struct dvobj_priv *)
					 pintfpriv->intf_dev;
	struct usb_device *udev = pdvobjpriv->pusbdev;
	/* For mstar platform, mstar suggests the address for USB IO
	 * should be 16 bytes alignment. Trying to fix it here.
	 */
	u8 *palloc_buf, *pIo_buf;

	palloc_buf = kmalloc((u32)len + 16, GFP_ATOMIC);
	if (!palloc_buf)
		return -ENOMEM;
	pIo_buf = palloc_buf + 16 - ((addr_t)(palloc_buf) & 0x0f);
	if (requesttype == 0x01) {
		pipe = usb_rcvctrlpipe(udev, 0); /* read_in */
		reqtype =  RTL871X_VENQT_READ;
	} else {
		pipe = usb_sndctrlpipe(udev, 0); /* write_out */
		reqtype =  RTL871X_VENQT_WRITE;
		memcpy(pIo_buf, pdata, len);
	}
	status = usb_control_msg(udev, pipe, request, reqtype, value, index,
				 pIo_buf, len, HZ / 2);
	if (status > 0) {  /* Success this control transfer. */
		if (requesttype == 0x01) {
			/* For Control read transfer, we have to copy the read
			 * data from pIo_buf to pdata.
			 */
			memcpy(pdata, pIo_buf,  status);
		}
	}
	kfree(palloc_buf);
	return status;
}