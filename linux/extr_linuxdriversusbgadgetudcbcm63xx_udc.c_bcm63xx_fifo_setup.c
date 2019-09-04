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
typedef  int u32 ;
struct iudma_ch_cfg {int n_fifo_slots; int max_pkt_hs; int max_pkt_fs; } ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct bcm63xx_udc {TYPE_1__ gadget; } ;

/* Variables and functions */
 int BCM63XX_NUM_IUDMA ; 
 int USBD_RXFIFO_CONFIG_END_SHIFT ; 
 int /*<<< orphan*/  USBD_RXFIFO_CONFIG_REG ; 
 int USBD_RXFIFO_CONFIG_START_SHIFT ; 
 int /*<<< orphan*/  USBD_RXFIFO_EPSIZE_REG ; 
 int USBD_TXFIFO_CONFIG_END_SHIFT ; 
 int /*<<< orphan*/  USBD_TXFIFO_CONFIG_REG ; 
 int USBD_TXFIFO_CONFIG_START_SHIFT ; 
 int /*<<< orphan*/  USBD_TXFIFO_EPSIZE_REG ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  bcm63xx_ep_dma_select (struct bcm63xx_udc*,int) ; 
 struct iudma_ch_cfg* iudma_defaults ; 
 int /*<<< orphan*/  usbd_readl (struct bcm63xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_writel (struct bcm63xx_udc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm63xx_fifo_setup(struct bcm63xx_udc *udc)
{
	int is_hs = udc->gadget.speed == USB_SPEED_HIGH;
	u32 i, val, rx_fifo_slot, tx_fifo_slot;

	/* set up FIFO boundaries and packet sizes; this is done in pairs */
	rx_fifo_slot = tx_fifo_slot = 0;
	for (i = 0; i < BCM63XX_NUM_IUDMA; i += 2) {
		const struct iudma_ch_cfg *rx_cfg = &iudma_defaults[i];
		const struct iudma_ch_cfg *tx_cfg = &iudma_defaults[i + 1];

		bcm63xx_ep_dma_select(udc, i >> 1);

		val = (rx_fifo_slot << USBD_RXFIFO_CONFIG_START_SHIFT) |
			((rx_fifo_slot + rx_cfg->n_fifo_slots - 1) <<
			 USBD_RXFIFO_CONFIG_END_SHIFT);
		rx_fifo_slot += rx_cfg->n_fifo_slots;
		usbd_writel(udc, val, USBD_RXFIFO_CONFIG_REG);
		usbd_writel(udc,
			    is_hs ? rx_cfg->max_pkt_hs : rx_cfg->max_pkt_fs,
			    USBD_RXFIFO_EPSIZE_REG);

		val = (tx_fifo_slot << USBD_TXFIFO_CONFIG_START_SHIFT) |
			((tx_fifo_slot + tx_cfg->n_fifo_slots - 1) <<
			 USBD_TXFIFO_CONFIG_END_SHIFT);
		tx_fifo_slot += tx_cfg->n_fifo_slots;
		usbd_writel(udc, val, USBD_TXFIFO_CONFIG_REG);
		usbd_writel(udc,
			    is_hs ? tx_cfg->max_pkt_hs : tx_cfg->max_pkt_fs,
			    USBD_TXFIFO_EPSIZE_REG);

		usbd_readl(udc, USBD_TXFIFO_EPSIZE_REG);
	}
}