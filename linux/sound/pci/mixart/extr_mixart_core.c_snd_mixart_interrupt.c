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
struct mixart_mgr {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int MIXART_HOST_ALL_INTERRUPT_MASKED ; 
 int MIXART_OIDI ; 
 int /*<<< orphan*/  MIXART_PCI_ODBR_OFFSET ; 
 int /*<<< orphan*/  MIXART_PCI_OMIMR_OFFSET ; 
 int /*<<< orphan*/  MIXART_PCI_OMISR_OFFSET ; 
 int /*<<< orphan*/  MIXART_REG (struct mixart_mgr*,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int readl_le (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_le (int,int /*<<< orphan*/ ) ; 

irqreturn_t snd_mixart_interrupt(int irq, void *dev_id)
{
	struct mixart_mgr *mgr = dev_id;
	u32 it_reg;

	it_reg = readl_le(MIXART_REG(mgr, MIXART_PCI_OMISR_OFFSET));
	if( !(it_reg & MIXART_OIDI) ) {
		/* this device did not cause the interrupt */
		return IRQ_NONE;
	}

	/* mask all interrupts */
	writel_le(MIXART_HOST_ALL_INTERRUPT_MASKED, MIXART_REG(mgr, MIXART_PCI_OMIMR_OFFSET));

	/* outdoorbell register clear */
	it_reg = readl(MIXART_REG(mgr, MIXART_PCI_ODBR_OFFSET));
	writel(it_reg, MIXART_REG(mgr, MIXART_PCI_ODBR_OFFSET));

	/* clear interrupt */
	writel_le( MIXART_OIDI, MIXART_REG(mgr, MIXART_PCI_OMISR_OFFSET) );

	return IRQ_WAKE_THREAD;
}