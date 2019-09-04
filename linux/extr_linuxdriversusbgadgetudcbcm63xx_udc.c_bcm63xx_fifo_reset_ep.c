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
typedef  int /*<<< orphan*/  u32 ;
struct bcm63xx_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_CONTROL_FIFO_RESET_MASK ; 
 int /*<<< orphan*/  USBD_CONTROL_REG ; 
 int /*<<< orphan*/  bcm63xx_ep_dma_select (struct bcm63xx_udc*,int) ; 
 int /*<<< orphan*/  usbd_readl (struct bcm63xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_writel (struct bcm63xx_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm63xx_fifo_reset_ep(struct bcm63xx_udc *udc, int ep_num)
{
	u32 val;

	bcm63xx_ep_dma_select(udc, ep_num);

	val = usbd_readl(udc, USBD_CONTROL_REG);
	val |= USBD_CONTROL_FIFO_RESET_MASK;
	usbd_writel(udc, val, USBD_CONTROL_REG);
	usbd_readl(udc, USBD_CONTROL_REG);
}