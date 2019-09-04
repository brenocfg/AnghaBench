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
struct bcm63xx_udc {int dummy; } ;

/* Variables and functions */
 int USBD_CONTROL_INIT_SEL_MASK ; 
 int USBD_CONTROL_INIT_SEL_SHIFT ; 
 int /*<<< orphan*/  USBD_CONTROL_REG ; 
 int usbd_readl (struct bcm63xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_writel (struct bcm63xx_udc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm63xx_ep_dma_select(struct bcm63xx_udc *udc, int idx)
{
	u32 val = usbd_readl(udc, USBD_CONTROL_REG);

	val &= ~USBD_CONTROL_INIT_SEL_MASK;
	val |= idx << USBD_CONTROL_INIT_SEL_SHIFT;
	usbd_writel(udc, val, USBD_CONTROL_REG);
}