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
struct lpc32xx_udc {int realized_eps; int /*<<< orphan*/  udp_baseaddr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_DEVINTCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_DEVINTST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_EPIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_EPMAXPSIZE (int /*<<< orphan*/ ) ; 
 int USBD_EP_RLZED ; 
 int /*<<< orphan*/  USBD_REEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_realize_hwep(struct lpc32xx_udc *udc, u32 hwep,
			     u32 maxpacket)
{
	int to = 1000;

	writel(USBD_EP_RLZED, USBD_DEVINTCLR(udc->udp_baseaddr));
	writel(hwep, USBD_EPIND(udc->udp_baseaddr));
	udc->realized_eps |= (1 << hwep);
	writel(udc->realized_eps, USBD_REEP(udc->udp_baseaddr));
	writel(maxpacket, USBD_EPMAXPSIZE(udc->udp_baseaddr));

	/* Wait until endpoint is realized in hardware */
	while ((!(readl(USBD_DEVINTST(udc->udp_baseaddr)) &
		  USBD_EP_RLZED)) && (to > 0))
		to--;
	if (!to)
		dev_dbg(udc->dev, "EP not correctly realized in hardware\n");

	writel(USBD_EP_RLZED, USBD_DEVINTCLR(udc->udp_baseaddr));
}