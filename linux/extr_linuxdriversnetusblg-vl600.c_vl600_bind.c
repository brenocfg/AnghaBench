#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vl600_state {int dummy; } ;
struct usbnet {TYPE_1__* net; struct vl600_state* driver_priv; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  kfree (struct vl600_state*) ; 
 struct vl600_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int usbnet_cdc_bind (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int vl600_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int ret;
	struct vl600_state *s = kzalloc(sizeof(struct vl600_state), GFP_KERNEL);

	if (!s)
		return -ENOMEM;

	ret = usbnet_cdc_bind(dev, intf);
	if (ret) {
		kfree(s);
		return ret;
	}

	dev->driver_priv = s;

	/* ARP packets don't go through, but they're also of no use.  The
	 * subnet has only two hosts anyway: us and the gateway / DHCP
	 * server (probably simulated by modem firmware or network operator)
	 * whose address changes everytime we connect to the intarwebz and
	 * who doesn't bother answering ARP requests either.  So hardware
	 * addresses have no meaning, the destination and the source of every
	 * packet depend only on whether it is on the IN or OUT endpoint.  */
	dev->net->flags |= IFF_NOARP;
	/* IPv6 NDP relies on multicast.  Enable it by default. */
	dev->net->flags |= IFF_MULTICAST;

	return ret;
}