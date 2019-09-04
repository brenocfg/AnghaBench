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
typedef  int u32 ;
struct lpc32xx_udc {int /*<<< orphan*/  udp_baseaddr; scalar_t__* udca_v_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CFG_DEV ; 
 int /*<<< orphan*/  CMD_SET_DEV_STAT ; 
 int /*<<< orphan*/  DAT_WR_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_DMAINTEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_DMARCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_EOTINTCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_NDDRTINTCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_SYSERRTINTCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_UDCAH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uda_clear_hwepint (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  uda_disable_devint (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  uda_disable_hwepint (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  udc_disable_hwep (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  udc_ep_dma_disable (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  udc_protocol_cmd_data_w (struct lpc32xx_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_unrealize_hwep (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_disable(struct lpc32xx_udc *udc)
{
	u32 i;

	/* Disable device */
	udc_protocol_cmd_data_w(udc, CMD_CFG_DEV, DAT_WR_BYTE(0));
	udc_protocol_cmd_data_w(udc, CMD_SET_DEV_STAT, DAT_WR_BYTE(0));

	/* Disable all device interrupts (including EP0) */
	uda_disable_devint(udc, 0x3FF);

	/* Disable and reset all endpoint interrupts */
	for (i = 0; i < 32; i++) {
		uda_disable_hwepint(udc, i);
		uda_clear_hwepint(udc, i);
		udc_disable_hwep(udc, i);
		udc_unrealize_hwep(udc, i);
		udc->udca_v_base[i] = 0;

		/* Disable and clear all interrupts and DMA */
		udc_ep_dma_disable(udc, i);
		writel((1 << i), USBD_EOTINTCLR(udc->udp_baseaddr));
		writel((1 << i), USBD_NDDRTINTCLR(udc->udp_baseaddr));
		writel((1 << i), USBD_SYSERRTINTCLR(udc->udp_baseaddr));
		writel((1 << i), USBD_DMARCLR(udc->udp_baseaddr));
	}

	/* Disable DMA interrupts */
	writel(0, USBD_DMAINTEN(udc->udp_baseaddr));

	writel(0, USBD_UDCAH(udc->udp_baseaddr));
}