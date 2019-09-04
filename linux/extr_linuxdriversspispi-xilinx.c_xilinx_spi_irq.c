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
struct xilinx_spi {int (* read_fn ) (scalar_t__) ;int /*<<< orphan*/  done; scalar_t__ regs; int /*<<< orphan*/  (* write_fn ) (int,scalar_t__) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ XIPIF_V123B_IISR_OFFSET ; 
 int XSPI_INTR_TX_EMPTY ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t xilinx_spi_irq(int irq, void *dev_id)
{
	struct xilinx_spi *xspi = dev_id;
	u32 ipif_isr;

	/* Get the IPIF interrupts, and clear them immediately */
	ipif_isr = xspi->read_fn(xspi->regs + XIPIF_V123B_IISR_OFFSET);
	xspi->write_fn(ipif_isr, xspi->regs + XIPIF_V123B_IISR_OFFSET);

	if (ipif_isr & XSPI_INTR_TX_EMPTY) {	/* Transmission completed */
		complete(&xspi->done);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}