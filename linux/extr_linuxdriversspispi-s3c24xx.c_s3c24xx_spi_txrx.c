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
struct spi_transfer {int len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int dummy; } ;
struct s3c24xx_spi {int len; int count; int /*<<< orphan*/  done; scalar_t__ regs; scalar_t__ fiq_inuse; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 scalar_t__ S3C2410_SPTDAT ; 
 int /*<<< orphan*/  hw_txbyte (struct s3c24xx_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s3c24xx_spi_tryfiq (struct s3c24xx_spi*) ; 
 scalar_t__ s3c24xx_spi_usefiq (struct s3c24xx_spi*) ; 
 struct s3c24xx_spi* to_hw (struct spi_device*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s3c24xx_spi_txrx(struct spi_device *spi, struct spi_transfer *t)
{
	struct s3c24xx_spi *hw = to_hw(spi);

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	hw->len = t->len;
	hw->count = 0;

	init_completion(&hw->done);

	hw->fiq_inuse = 0;
	if (s3c24xx_spi_usefiq(hw) && t->len >= 3)
		s3c24xx_spi_tryfiq(hw);

	/* send the first byte */
	writeb(hw_txbyte(hw, 0), hw->regs + S3C2410_SPTDAT);

	wait_for_completion(&hw->done);
	return hw->count;
}