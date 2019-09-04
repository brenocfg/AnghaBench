#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct iudma_ch_cfg {int max_pkt_hs; int max_pkt_fs; int ep_num; int dir; int ep_type; } ;
struct TYPE_4__ {scalar_t__ speed; } ;
struct bcm63xx_udc {int cfg; int iface; int alt_iface; TYPE_3__* bep; TYPE_2__* iudma; TYPE_1__ gadget; } ;
struct TYPE_6__ {int /*<<< orphan*/  ep; } ;
struct TYPE_5__ {int max_pkt; } ;

/* Variables and functions */
 size_t BCM63XX_NUM_IUDMA ; 
 int USBD_CSR_EP_ALTIFACE_SHIFT ; 
 int USBD_CSR_EP_CFG_SHIFT ; 
 int USBD_CSR_EP_DIR_SHIFT ; 
 int USBD_CSR_EP_IFACE_SHIFT ; 
 int USBD_CSR_EP_LOG_SHIFT ; 
 int USBD_CSR_EP_MAXPKT_SHIFT ; 
 int /*<<< orphan*/  USBD_CSR_EP_REG (int) ; 
 int USBD_CSR_EP_TYPE_SHIFT ; 
 size_t USBD_CSR_SETUPADDR_DEF ; 
 int /*<<< orphan*/  USBD_CSR_SETUPADDR_REG ; 
 scalar_t__ USB_SPEED_HIGH ; 
 struct iudma_ch_cfg* iudma_defaults ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbd_writel (struct bcm63xx_udc*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm63xx_ep_setup(struct bcm63xx_udc *udc)
{
	u32 val, i;

	usbd_writel(udc, USBD_CSR_SETUPADDR_DEF, USBD_CSR_SETUPADDR_REG);

	for (i = 0; i < BCM63XX_NUM_IUDMA; i++) {
		const struct iudma_ch_cfg *cfg = &iudma_defaults[i];
		int max_pkt = udc->gadget.speed == USB_SPEED_HIGH ?
			      cfg->max_pkt_hs : cfg->max_pkt_fs;
		int idx = cfg->ep_num;

		udc->iudma[i].max_pkt = max_pkt;

		if (idx < 0)
			continue;
		usb_ep_set_maxpacket_limit(&udc->bep[idx].ep, max_pkt);

		val = (idx << USBD_CSR_EP_LOG_SHIFT) |
		      (cfg->dir << USBD_CSR_EP_DIR_SHIFT) |
		      (cfg->ep_type << USBD_CSR_EP_TYPE_SHIFT) |
		      (udc->cfg << USBD_CSR_EP_CFG_SHIFT) |
		      (udc->iface << USBD_CSR_EP_IFACE_SHIFT) |
		      (udc->alt_iface << USBD_CSR_EP_ALTIFACE_SHIFT) |
		      (max_pkt << USBD_CSR_EP_MAXPKT_SHIFT);
		usbd_writel(udc, val, USBD_CSR_EP_REG(idx));
	}
}