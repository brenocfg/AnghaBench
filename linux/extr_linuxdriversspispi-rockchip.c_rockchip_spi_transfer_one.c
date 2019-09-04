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
struct spi_transfer {scalar_t__ tx_buf; scalar_t__ rx_buf; scalar_t__ len; int bits_per_word; int /*<<< orphan*/  rx_sg; int /*<<< orphan*/  tx_sg; int /*<<< orphan*/  speed_hz; } ;
struct spi_master {scalar_t__ (* can_dma ) (struct spi_master*,struct spi_device*,struct spi_transfer*) ;} ;
struct spi_device {int dummy; } ;
struct rockchip_spi {int bpw; int n_bytes; scalar_t__ tx; scalar_t__ tx_end; scalar_t__ rx; scalar_t__ rx_end; scalar_t__ len; scalar_t__ tmode; int use_dma; int /*<<< orphan*/  rx_sg; int /*<<< orphan*/  tx_sg; int /*<<< orphan*/  speed; int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ CR0_XFM_RO ; 
 scalar_t__ CR0_XFM_TO ; 
 scalar_t__ CR0_XFM_TR ; 
 int EINVAL ; 
 scalar_t__ ROCKCHIP_SPI_MAX_TRANLEN ; 
 scalar_t__ ROCKCHIP_SPI_SR ; 
 scalar_t__ ROCKCHIP_SPI_SSIENR ; 
 int SR_BUSY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  rockchip_spi_config (struct rockchip_spi*) ; 
 int rockchip_spi_pio_transfer (struct rockchip_spi*) ; 
 int rockchip_spi_prepare_dma (struct rockchip_spi*) ; 
 int /*<<< orphan*/  spi_enable_chip (struct rockchip_spi*,int) ; 
 struct rockchip_spi* spi_master_get_devdata (struct spi_master*) ; 
 scalar_t__ stub1 (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 

__attribute__((used)) static int rockchip_spi_transfer_one(
		struct spi_master *master,
		struct spi_device *spi,
		struct spi_transfer *xfer)
{
	int ret = 0;
	struct rockchip_spi *rs = spi_master_get_devdata(master);

	WARN_ON(readl_relaxed(rs->regs + ROCKCHIP_SPI_SSIENR) &&
		(readl_relaxed(rs->regs + ROCKCHIP_SPI_SR) & SR_BUSY));

	if (!xfer->tx_buf && !xfer->rx_buf) {
		dev_err(rs->dev, "No buffer for transfer\n");
		return -EINVAL;
	}

	if (xfer->len > ROCKCHIP_SPI_MAX_TRANLEN) {
		dev_err(rs->dev, "Transfer is too long (%d)\n", xfer->len);
		return -EINVAL;
	}

	rs->speed = xfer->speed_hz;
	rs->bpw = xfer->bits_per_word;
	rs->n_bytes = rs->bpw >> 3;

	rs->tx = xfer->tx_buf;
	rs->tx_end = rs->tx + xfer->len;
	rs->rx = xfer->rx_buf;
	rs->rx_end = rs->rx + xfer->len;
	rs->len = xfer->len;

	rs->tx_sg = xfer->tx_sg;
	rs->rx_sg = xfer->rx_sg;

	if (rs->tx && rs->rx)
		rs->tmode = CR0_XFM_TR;
	else if (rs->tx)
		rs->tmode = CR0_XFM_TO;
	else if (rs->rx)
		rs->tmode = CR0_XFM_RO;

	/* we need prepare dma before spi was enabled */
	if (master->can_dma && master->can_dma(master, spi, xfer))
		rs->use_dma = 1;
	else
		rs->use_dma = 0;

	rockchip_spi_config(rs);

	if (rs->use_dma) {
		if (rs->tmode == CR0_XFM_RO) {
			/* rx: dma must be prepared first */
			ret = rockchip_spi_prepare_dma(rs);
			spi_enable_chip(rs, 1);
		} else {
			/* tx or tr: spi must be enabled first */
			spi_enable_chip(rs, 1);
			ret = rockchip_spi_prepare_dma(rs);
		}
		/* successful DMA prepare means the transfer is in progress */
		ret = ret ? ret : 1;
	} else {
		spi_enable_chip(rs, 1);
		ret = rockchip_spi_pio_transfer(rs);
	}

	return ret;
}