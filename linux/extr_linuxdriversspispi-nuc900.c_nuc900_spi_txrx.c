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
struct spi_transfer {int /*<<< orphan*/  len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int dummy; } ;
struct nuc900_spi {int count; int /*<<< orphan*/  done; scalar_t__ regs; int /*<<< orphan*/  len; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 scalar_t__ USI_TX0 ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hw_txbyte (struct nuc900_spi*,int) ; 
 int /*<<< orphan*/  nuc900_spi_gobusy (struct nuc900_spi*) ; 
 struct nuc900_spi* to_hw (struct spi_device*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nuc900_spi_txrx(struct spi_device *spi, struct spi_transfer *t)
{
	struct nuc900_spi *hw = to_hw(spi);

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	hw->len = t->len;
	hw->count = 0;

	__raw_writel(hw_txbyte(hw, 0x0), hw->regs + USI_TX0);

	nuc900_spi_gobusy(hw);

	wait_for_completion(&hw->done);

	return hw->count;
}