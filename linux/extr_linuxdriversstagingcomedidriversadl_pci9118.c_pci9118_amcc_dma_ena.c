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
struct pci9118_private {scalar_t__ iobase_a; } ;
struct comedi_device {struct pci9118_private* private; } ;

/* Variables and functions */
 unsigned int A2P_HI_PRIORITY ; 
 scalar_t__ AMCC_OP_REG_MCSR ; 
 unsigned int EN_A2P_TRANSFERS ; 
 unsigned int RESET_A2P_FLAGS ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static void pci9118_amcc_dma_ena(struct comedi_device *dev, bool enable)
{
	struct pci9118_private *devpriv = dev->private;
	unsigned int mcsr;

	mcsr = inl(devpriv->iobase_a + AMCC_OP_REG_MCSR);
	if (enable)
		mcsr |= RESET_A2P_FLAGS | A2P_HI_PRIORITY | EN_A2P_TRANSFERS;
	else
		mcsr &= ~EN_A2P_TRANSFERS;
	outl(mcsr, devpriv->iobase_a + AMCC_OP_REG_MCSR);
}