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
struct tsi721_device {int flags; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ TSI721_DEV_CHAN_INTE ; 
 scalar_t__ TSI721_IBDMAC_INT (int) ; 
 scalar_t__ TSI721_IBDMAC_INTE (int) ; 
 int TSI721_INT_IMSG_CHAN (int) ; 
 int TSI721_USING_MSIX ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void
tsi721_imsg_interrupt_enable(struct tsi721_device *priv, int ch,
				  u32 inte_mask)
{
	u32 rval;

	if (!inte_mask)
		return;

	/* Clear pending Inbound Messaging interrupts */
	iowrite32(inte_mask, priv->regs + TSI721_IBDMAC_INT(ch));

	/* Enable Inbound Messaging interrupts */
	rval = ioread32(priv->regs + TSI721_IBDMAC_INTE(ch));
	iowrite32(rval | inte_mask, priv->regs + TSI721_IBDMAC_INTE(ch));

	if (priv->flags & TSI721_USING_MSIX)
		return; /* Finished if we are in MSI-X mode */

	/*
	 * For MSI and INTA interrupt signalling we need to enable next levels
	 */

	/* Enable Device Channel Interrupt */
	rval = ioread32(priv->regs + TSI721_DEV_CHAN_INTE);
	iowrite32(rval | TSI721_INT_IMSG_CHAN(ch),
		  priv->regs + TSI721_DEV_CHAN_INTE);
}