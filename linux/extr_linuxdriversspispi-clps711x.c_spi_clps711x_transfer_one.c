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
typedef  int u8 ;
struct spi_transfer {scalar_t__ rx_buf; scalar_t__ tx_buf; int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  len; scalar_t__ speed_hz; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  max_speed_hz; } ;
struct spi_clps711x_data {int* tx_buf; int* rx_buf; int /*<<< orphan*/  syncio; int /*<<< orphan*/  bpw; int /*<<< orphan*/  len; int /*<<< orphan*/  spi_clk; } ;

/* Variables and functions */
 int SYNCIO_FRMLEN (int /*<<< orphan*/ ) ; 
 int SYNCIO_TXFRMEN ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct spi_clps711x_data* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_clps711x_transfer_one(struct spi_master *master,
				     struct spi_device *spi,
				     struct spi_transfer *xfer)
{
	struct spi_clps711x_data *hw = spi_master_get_devdata(master);
	u8 data;

	clk_set_rate(hw->spi_clk, xfer->speed_hz ? : spi->max_speed_hz);

	hw->len = xfer->len;
	hw->bpw = xfer->bits_per_word;
	hw->tx_buf = (u8 *)xfer->tx_buf;
	hw->rx_buf = (u8 *)xfer->rx_buf;

	/* Initiate transfer */
	data = hw->tx_buf ? *hw->tx_buf++ : 0;
	writel(data | SYNCIO_FRMLEN(hw->bpw) | SYNCIO_TXFRMEN, hw->syncio);

	return 1;
}