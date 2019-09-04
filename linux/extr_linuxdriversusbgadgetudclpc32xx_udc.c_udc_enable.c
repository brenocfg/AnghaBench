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
struct lpc32xx_udc {int udca_p_base; scalar_t__ dev_status; int /*<<< orphan*/  udp_baseaddr; struct lpc32xx_ep* ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  maxpacket; } ;
struct lpc32xx_ep {TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_DEV_STAT ; 
 int /*<<< orphan*/  DAT_WR_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEV_CON ; 
 int /*<<< orphan*/  USBD_DEVINTCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_DEVINTPRI (int /*<<< orphan*/ ) ; 
 int USBD_DEV_STAT ; 
 int /*<<< orphan*/  USBD_DMAINTEN (int /*<<< orphan*/ ) ; 
 int USBD_EOT_INT ; 
 int /*<<< orphan*/  USBD_EPINTPRI (int /*<<< orphan*/ ) ; 
 int USBD_EP_FAST ; 
 int USBD_EP_SLOW ; 
 int USBD_ERR_INT ; 
 int USBD_SYS_ERR_INT ; 
 int /*<<< orphan*/  USBD_UDCAH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uda_clear_devint (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  uda_enable_devint (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  uda_enable_hwepint (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  udc_clr_buffer_hwep (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  udc_clrstall_hwep (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  udc_disable (struct lpc32xx_udc*) ; 
 int /*<<< orphan*/  udc_protocol_cmd_data_w (struct lpc32xx_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_realize_hwep (struct lpc32xx_udc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_select_hwep (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  udc_set_address (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_enable(struct lpc32xx_udc *udc)
{
	u32 i;
	struct lpc32xx_ep *ep = &udc->ep[0];

	/* Start with known state */
	udc_disable(udc);

	/* Enable device */
	udc_protocol_cmd_data_w(udc, CMD_SET_DEV_STAT, DAT_WR_BYTE(DEV_CON));

	/* EP interrupts on high priority, FRAME interrupt on low priority */
	writel(USBD_EP_FAST, USBD_DEVINTPRI(udc->udp_baseaddr));
	writel(0xFFFF, USBD_EPINTPRI(udc->udp_baseaddr));

	/* Clear any pending device interrupts */
	writel(0x3FF, USBD_DEVINTCLR(udc->udp_baseaddr));

	/* Setup UDCA - not yet used (DMA) */
	writel(udc->udca_p_base, USBD_UDCAH(udc->udp_baseaddr));

	/* Only enable EP0 in and out for now, EP0 only works in FIFO mode */
	for (i = 0; i <= 1; i++) {
		udc_realize_hwep(udc, i, ep->ep.maxpacket);
		uda_enable_hwepint(udc, i);
		udc_select_hwep(udc, i);
		udc_clrstall_hwep(udc, i);
		udc_clr_buffer_hwep(udc, i);
	}

	/* Device interrupt setup */
	uda_clear_devint(udc, (USBD_ERR_INT | USBD_DEV_STAT | USBD_EP_SLOW |
			       USBD_EP_FAST));
	uda_enable_devint(udc, (USBD_ERR_INT | USBD_DEV_STAT | USBD_EP_SLOW |
				USBD_EP_FAST));

	/* Set device address to 0 - called twice to force a latch in the USB
	   engine without the need of a setup packet status closure */
	udc_set_address(udc, 0);
	udc_set_address(udc, 0);

	/* Enable master DMA interrupts */
	writel((USBD_SYS_ERR_INT | USBD_EOT_INT),
		     USBD_DMAINTEN(udc->udp_baseaddr));

	udc->dev_status = 0;
}