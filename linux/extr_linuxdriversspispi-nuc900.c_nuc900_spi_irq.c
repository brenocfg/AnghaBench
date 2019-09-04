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
struct nuc900_spi {unsigned int count; unsigned int len; int /*<<< orphan*/  done; scalar_t__ regs; void** rx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int ENFLG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ USI_CNT ; 
 scalar_t__ USI_RX0 ; 
 scalar_t__ USI_TX0 ; 
 void* __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 unsigned int hw_txbyte (struct nuc900_spi*,unsigned int) ; 
 int /*<<< orphan*/  nuc900_spi_gobusy (struct nuc900_spi*) ; 

__attribute__((used)) static irqreturn_t nuc900_spi_irq(int irq, void *dev)
{
	struct nuc900_spi *hw = dev;
	unsigned int status;
	unsigned int count = hw->count;

	status = __raw_readl(hw->regs + USI_CNT);
	__raw_writel(status, hw->regs + USI_CNT);

	if (status & ENFLG) {
		hw->count++;

		if (hw->rx)
			hw->rx[count] = __raw_readl(hw->regs + USI_RX0);
		count++;

		if (count < hw->len) {
			__raw_writel(hw_txbyte(hw, count), hw->regs + USI_TX0);
			nuc900_spi_gobusy(hw);
		} else {
			complete(&hw->done);
		}

		return IRQ_HANDLED;
	}

	complete(&hw->done);
	return IRQ_HANDLED;
}