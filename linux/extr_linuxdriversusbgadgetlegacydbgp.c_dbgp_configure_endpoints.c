#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  bDebugOutEndpoint; int /*<<< orphan*/  bDebugInEndpoint; } ;
struct TYPE_9__ {TYPE_1__* gadget; void* o_ep; void* i_ep; } ;
struct TYPE_8__ {int /*<<< orphan*/  bEndpointAddress; void* wMaxPacketSize; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  USB_DEBUG_MAX_PACKET_SIZE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 TYPE_6__ dbg_desc ; 
 TYPE_5__ dbgp ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_2__ i_desc ; 
 TYPE_2__ o_desc ; 
 void* usb_ep_autoconfig (struct usb_gadget*,TYPE_2__*) ; 
 int /*<<< orphan*/  usb_ep_autoconfig_reset (struct usb_gadget*) ; 

__attribute__((used)) static int dbgp_configure_endpoints(struct usb_gadget *gadget)
{
	int stp;

	usb_ep_autoconfig_reset(gadget);

	dbgp.i_ep = usb_ep_autoconfig(gadget, &i_desc);
	if (!dbgp.i_ep) {
		stp = 1;
		goto fail_1;
	}

	i_desc.wMaxPacketSize =
		cpu_to_le16(USB_DEBUG_MAX_PACKET_SIZE);

	dbgp.o_ep = usb_ep_autoconfig(gadget, &o_desc);
	if (!dbgp.o_ep) {
		stp = 2;
		goto fail_1;
	}

	o_desc.wMaxPacketSize =
		cpu_to_le16(USB_DEBUG_MAX_PACKET_SIZE);

	dbg_desc.bDebugInEndpoint = i_desc.bEndpointAddress;
	dbg_desc.bDebugOutEndpoint = o_desc.bEndpointAddress;

#ifdef CONFIG_USB_G_DBGP_SERIAL
	dbgp.serial->in = dbgp.i_ep;
	dbgp.serial->out = dbgp.o_ep;

	dbgp.serial->in->desc = &i_desc;
	dbgp.serial->out->desc = &o_desc;
#endif

	return 0;

fail_1:
	dev_dbg(&dbgp.gadget->dev, "ep config: failure (%d)\n", stp);
	return -ENODEV;
}