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
struct vmk80xx_private {int /*<<< orphan*/  limit_sem; int /*<<< orphan*/  usb_tx_buf; int /*<<< orphan*/  usb_rx_buf; } ;
struct usb_interface {int dummy; } ;
struct comedi_device {struct vmk80xx_private* private; } ;

/* Variables and functions */
 struct usb_interface* comedi_to_usb_interface (struct comedi_device*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmk80xx_detach(struct comedi_device *dev)
{
	struct usb_interface *intf = comedi_to_usb_interface(dev);
	struct vmk80xx_private *devpriv = dev->private;

	if (!devpriv)
		return;

	down(&devpriv->limit_sem);

	usb_set_intfdata(intf, NULL);

	kfree(devpriv->usb_rx_buf);
	kfree(devpriv->usb_tx_buf);

	up(&devpriv->limit_sem);
}