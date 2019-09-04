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
typedef  unsigned long u8 ;
struct aac_dev {unsigned long OIMR; TYPE_2__* queues; TYPE_1__* IndexRegs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  ODR; int /*<<< orphan*/  OISR; } ;
struct TYPE_5__ {int /*<<< orphan*/ * queue; } ;
struct TYPE_4__ {int /*<<< orphan*/ * Mailbox; } ;

/* Variables and functions */
 unsigned long DoorBellAdapterNormCmdNotFull ; 
 unsigned long DoorBellAdapterNormCmdReady ; 
 unsigned long DoorBellAdapterNormRespNotFull ; 
 unsigned long DoorBellAdapterNormRespReady ; 
 unsigned long DoorBellPrintfDone ; 
 unsigned long DoorBellPrintfReady ; 
 size_t HostNormCmdQueue ; 
 size_t HostNormRespQueue ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  InboundDoorbellReg ; 
 TYPE_3__ MUnit ; 
 int /*<<< orphan*/  OutboundDoorbellReg ; 
 int /*<<< orphan*/  aac_command_normal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aac_printf (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_response_normal (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (unsigned long) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 unsigned long rx_readb (struct aac_dev*,int /*<<< orphan*/ ) ; 
 unsigned long rx_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_writel (struct aac_dev*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static irqreturn_t aac_rx_intr_producer(int irq, void *dev_id)
{
	struct aac_dev *dev = dev_id;
	unsigned long bellbits;
	u8 intstat = rx_readb(dev, MUnit.OISR);

	/*
	 *	Read mask and invert because drawbridge is reversed.
	 *	This allows us to only service interrupts that have
	 *	been enabled.
	 *	Check to see if this is our interrupt.  If it isn't just return
	 */
	if (likely(intstat & ~(dev->OIMR))) {
		bellbits = rx_readl(dev, OutboundDoorbellReg);
		if (unlikely(bellbits & DoorBellPrintfReady)) {
			aac_printf(dev, readl (&dev->IndexRegs->Mailbox[5]));
			rx_writel(dev, MUnit.ODR,DoorBellPrintfReady);
			rx_writel(dev, InboundDoorbellReg,DoorBellPrintfDone);
		}
		else if (unlikely(bellbits & DoorBellAdapterNormCmdReady)) {
			rx_writel(dev, MUnit.ODR, DoorBellAdapterNormCmdReady);
			aac_command_normal(&dev->queues->queue[HostNormCmdQueue]);
		}
		else if (likely(bellbits & DoorBellAdapterNormRespReady)) {
			rx_writel(dev, MUnit.ODR,DoorBellAdapterNormRespReady);
			aac_response_normal(&dev->queues->queue[HostNormRespQueue]);
		}
		else if (unlikely(bellbits & DoorBellAdapterNormCmdNotFull)) {
			rx_writel(dev, MUnit.ODR, DoorBellAdapterNormCmdNotFull);
		}
		else if (unlikely(bellbits & DoorBellAdapterNormRespNotFull)) {
			rx_writel(dev, MUnit.ODR, DoorBellAdapterNormCmdNotFull);
			rx_writel(dev, MUnit.ODR, DoorBellAdapterNormRespNotFull);
		}
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}