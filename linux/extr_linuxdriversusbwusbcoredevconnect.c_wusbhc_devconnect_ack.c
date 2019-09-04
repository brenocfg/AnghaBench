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
struct TYPE_2__ {int /*<<< orphan*/  hdr; } ;
struct wusbhc {unsigned int ports_max; int /*<<< orphan*/  mutex; TYPE_1__ cack_ie; int /*<<< orphan*/  (* set_ptk ) (struct wusbhc*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;struct device* dev; } ;
struct wusb_port {int status; int /*<<< orphan*/  change; struct wusb_dev* wusb_dev; } ;
struct wusb_dn_connect {int /*<<< orphan*/  CDID; } ;
struct wusb_dev {int /*<<< orphan*/  cdid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int USB_PORT_STAT_CONNECTION ; 
 int /*<<< orphan*/  USB_PORT_STAT_C_CONNECTION ; 
 int USB_PORT_STAT_POWER ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int,char const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct wusbhc*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wusb_port* wusb_port_by_idx (struct wusbhc*,unsigned int) ; 
 struct wusb_dev* wusbhc_cack_add (struct wusbhc*,struct wusb_dn_connect*,char const*,unsigned int) ; 
 int wusbhc_mmcie_set (struct wusbhc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void wusbhc_devconnect_ack(struct wusbhc *wusbhc, struct wusb_dn_connect *dnc,
			   const char *pr_cdid)
{
	int result;
	struct device *dev = wusbhc->dev;
	struct wusb_dev *wusb_dev;
	struct wusb_port *port;
	unsigned idx;

	mutex_lock(&wusbhc->mutex);

	/* Check we are not handling it already */
	for (idx = 0; idx < wusbhc->ports_max; idx++) {
		port = wusb_port_by_idx(wusbhc, idx);
		if (port->wusb_dev
		    && memcmp(&dnc->CDID, &port->wusb_dev->cdid, sizeof(dnc->CDID)) == 0)
			goto error_unlock;
	}
	/* Look up those fake ports we have for a free one */
	for (idx = 0; idx < wusbhc->ports_max; idx++) {
		port = wusb_port_by_idx(wusbhc, idx);
		if ((port->status & USB_PORT_STAT_POWER)
		    && !(port->status & USB_PORT_STAT_CONNECTION))
			break;
	}
	if (idx >= wusbhc->ports_max) {
		dev_err(dev, "Host controller can't connect more devices "
			"(%u already connected); device %s rejected\n",
			wusbhc->ports_max, pr_cdid);
		/* NOTE: we could send a WUIE_Disconnect here, but we haven't
		 *       event acked, so the device will eventually timeout the
		 *       connection, right? */
		goto error_unlock;
	}

	/* Make sure we are using no crypto on that "virtual port" */
	wusbhc->set_ptk(wusbhc, idx, 0, NULL, 0);

	/* Grab a filled in Connect-Ack context, fill out the
	 * Connect-Ack Wireless USB IE, set the MMC */
	wusb_dev = wusbhc_cack_add(wusbhc, dnc, pr_cdid, idx);
	if (wusb_dev == NULL)
		goto error_unlock;
	result = wusbhc_mmcie_set(wusbhc, 0, 0, &wusbhc->cack_ie.hdr);
	if (result < 0)
		goto error_unlock;
	/* Give the device at least 2ms (WUSB1.0[7.5.1p3]), let's do
	 * three for a good measure */
	msleep(3);
	port->wusb_dev = wusb_dev;
	port->status |= USB_PORT_STAT_CONNECTION;
	port->change |= USB_PORT_STAT_C_CONNECTION;
	/* Now the port status changed to connected; hub_wq will
	 * pick the change up and try to reset the port to bring it to
	 * the enabled state--so this process returns up to the stack
	 * and it calls back into wusbhc_rh_port_reset().
	 */
error_unlock:
	mutex_unlock(&wusbhc->mutex);
	return;

}