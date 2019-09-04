#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_phy {int dummy; } ;
struct platform_device {int dummy; } ;
struct TYPE_6__ {int quirk_ep_out_aligned_size; int /*<<< orphan*/  name; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  speed; int /*<<< orphan*/  ep_list; TYPE_2__* ep0; int /*<<< orphan*/ * ops; } ;
struct TYPE_9__ {TYPE_3__* ep; struct usb_phy* transceiver; TYPE_1__ gadget; int /*<<< orphan*/  iso; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  ep_list; } ;
struct TYPE_8__ {TYPE_2__ ep; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO (char*,int,int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int UDC_CFG_LOCK ; 
 int /*<<< orphan*/  UDC_DMA_IRQ_EN ; 
 int /*<<< orphan*/  UDC_EP_RX (unsigned int) ; 
 int /*<<< orphan*/  UDC_EP_TX (unsigned int) ; 
 int /*<<< orphan*/  UDC_IRQ_EN ; 
 int /*<<< orphan*/  UDC_IRQ_SRC ; 
 int UDC_IRQ_SRC_MASK ; 
 int /*<<< orphan*/  UDC_RXDMA_CFG ; 
 int UDC_SELF_PWR ; 
 int /*<<< orphan*/  UDC_SYSCON1 ; 
 int /*<<< orphan*/  UDC_TXDMA_CFG ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_BULK ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_CONTROL ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_INT ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  driver_name ; 
 int fifo_mode ; 
 TYPE_4__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 unsigned int omap_ep_setup (char*,int,int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/  omap_gadget_ops ; 
 int /*<<< orphan*/  omap_writew (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* udc ; 

__attribute__((used)) static int
omap_udc_setup(struct platform_device *odev, struct usb_phy *xceiv)
{
	unsigned	tmp, buf;

	/* abolish any previous hardware state */
	omap_writew(0, UDC_SYSCON1);
	omap_writew(0, UDC_IRQ_EN);
	omap_writew(UDC_IRQ_SRC_MASK, UDC_IRQ_SRC);
	omap_writew(0, UDC_DMA_IRQ_EN);
	omap_writew(0, UDC_RXDMA_CFG);
	omap_writew(0, UDC_TXDMA_CFG);

	/* UDC_PULLUP_EN gates the chip clock */
	/* OTG_SYSCON_1 |= DEV_IDLE_EN; */

	udc = kzalloc(sizeof(*udc), GFP_KERNEL);
	if (!udc)
		return -ENOMEM;

	spin_lock_init(&udc->lock);

	udc->gadget.ops = &omap_gadget_ops;
	udc->gadget.ep0 = &udc->ep[0].ep;
	INIT_LIST_HEAD(&udc->gadget.ep_list);
	INIT_LIST_HEAD(&udc->iso);
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->gadget.max_speed = USB_SPEED_FULL;
	udc->gadget.name = driver_name;
	udc->gadget.quirk_ep_out_aligned_size = 1;
	udc->transceiver = xceiv;

	/* ep0 is special; put it right after the SETUP buffer */
	buf = omap_ep_setup("ep0", 0, USB_ENDPOINT_XFER_CONTROL,
			8 /* after SETUP */, 64 /* maxpacket */, 0);
	list_del_init(&udc->ep[0].ep.ep_list);

	/* initially disable all non-ep0 endpoints */
	for (tmp = 1; tmp < 15; tmp++) {
		omap_writew(0, UDC_EP_RX(tmp));
		omap_writew(0, UDC_EP_TX(tmp));
	}

#define OMAP_BULK_EP(name, addr) \
	buf = omap_ep_setup(name "-bulk", addr, \
			USB_ENDPOINT_XFER_BULK, buf, 64, 1);
#define OMAP_INT_EP(name, addr, maxp) \
	buf = omap_ep_setup(name "-int", addr, \
			USB_ENDPOINT_XFER_INT, buf, maxp, 0);
#define OMAP_ISO_EP(name, addr, maxp) \
	buf = omap_ep_setup(name "-iso", addr, \
			USB_ENDPOINT_XFER_ISOC, buf, maxp, 1);

	switch (fifo_mode) {
	case 0:
		OMAP_BULK_EP("ep1in",  USB_DIR_IN  | 1);
		OMAP_BULK_EP("ep2out", USB_DIR_OUT | 2);
		OMAP_INT_EP("ep3in",   USB_DIR_IN  | 3, 16);
		break;
	case 1:
		OMAP_BULK_EP("ep1in",  USB_DIR_IN  | 1);
		OMAP_BULK_EP("ep2out", USB_DIR_OUT | 2);
		OMAP_INT_EP("ep9in",   USB_DIR_IN  | 9, 16);

		OMAP_BULK_EP("ep3in",  USB_DIR_IN  | 3);
		OMAP_BULK_EP("ep4out", USB_DIR_OUT | 4);
		OMAP_INT_EP("ep10in",  USB_DIR_IN  | 10, 16);

		OMAP_BULK_EP("ep5in",  USB_DIR_IN  | 5);
		OMAP_BULK_EP("ep5out", USB_DIR_OUT | 5);
		OMAP_INT_EP("ep11in",  USB_DIR_IN  | 11, 16);

		OMAP_BULK_EP("ep6in",  USB_DIR_IN  | 6);
		OMAP_BULK_EP("ep6out", USB_DIR_OUT | 6);
		OMAP_INT_EP("ep12in",  USB_DIR_IN  | 12, 16);

		OMAP_BULK_EP("ep7in",  USB_DIR_IN  | 7);
		OMAP_BULK_EP("ep7out", USB_DIR_OUT | 7);
		OMAP_INT_EP("ep13in",  USB_DIR_IN  | 13, 16);
		OMAP_INT_EP("ep13out", USB_DIR_OUT | 13, 16);

		OMAP_BULK_EP("ep8in",  USB_DIR_IN  | 8);
		OMAP_BULK_EP("ep8out", USB_DIR_OUT | 8);
		OMAP_INT_EP("ep14in",  USB_DIR_IN  | 14, 16);
		OMAP_INT_EP("ep14out", USB_DIR_OUT | 14, 16);

		OMAP_BULK_EP("ep15in",  USB_DIR_IN  | 15);
		OMAP_BULK_EP("ep15out", USB_DIR_OUT | 15);

		break;

#ifdef	USE_ISO
	case 2:			/* mixed iso/bulk */
		OMAP_ISO_EP("ep1in",   USB_DIR_IN  | 1, 256);
		OMAP_ISO_EP("ep2out",  USB_DIR_OUT | 2, 256);
		OMAP_ISO_EP("ep3in",   USB_DIR_IN  | 3, 128);
		OMAP_ISO_EP("ep4out",  USB_DIR_OUT | 4, 128);

		OMAP_INT_EP("ep5in",   USB_DIR_IN  | 5, 16);

		OMAP_BULK_EP("ep6in",  USB_DIR_IN  | 6);
		OMAP_BULK_EP("ep7out", USB_DIR_OUT | 7);
		OMAP_INT_EP("ep8in",   USB_DIR_IN  | 8, 16);
		break;
	case 3:			/* mixed bulk/iso */
		OMAP_BULK_EP("ep1in",  USB_DIR_IN  | 1);
		OMAP_BULK_EP("ep2out", USB_DIR_OUT | 2);
		OMAP_INT_EP("ep3in",   USB_DIR_IN  | 3, 16);

		OMAP_BULK_EP("ep4in",  USB_DIR_IN  | 4);
		OMAP_BULK_EP("ep5out", USB_DIR_OUT | 5);
		OMAP_INT_EP("ep6in",   USB_DIR_IN  | 6, 16);

		OMAP_ISO_EP("ep7in",   USB_DIR_IN  | 7, 256);
		OMAP_ISO_EP("ep8out",  USB_DIR_OUT | 8, 256);
		OMAP_INT_EP("ep9in",   USB_DIR_IN  | 9, 16);
		break;
#endif

	/* add more modes as needed */

	default:
		ERR("unsupported fifo_mode #%d\n", fifo_mode);
		return -ENODEV;
	}
	omap_writew(UDC_CFG_LOCK|UDC_SELF_PWR, UDC_SYSCON1);
	INFO("fifo mode %d, %d bytes not used\n", fifo_mode, 2048 - buf);
	return 0;
}