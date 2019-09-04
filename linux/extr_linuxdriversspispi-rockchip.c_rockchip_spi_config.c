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
struct rockchip_spi {int n_bytes; int mode; int tmode; int type; int speed; int max_freq; int rsd_nsecs; int len; int fifo_len; int /*<<< orphan*/  dev; scalar_t__ regs; int /*<<< orphan*/  spiclk; scalar_t__ rx; scalar_t__ tx; scalar_t__ use_dma; } ;

/* Variables and functions */
 int CR0_BHT_8BIT ; 
 int CR0_BHT_OFFSET ; 
 int CR0_DFS_OFFSET ; 
 int CR0_EM_BIG ; 
 int CR0_EM_OFFSET ; 
 int CR0_FRF_OFFSET ; 
 int CR0_RSD_OFFSET ; 
 int CR0_SCPH_OFFSET ; 
 int CR0_SSD_OFFSET ; 
 int CR0_SSD_ONE ; 
 int CR0_XFM_OFFSET ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int MAX_SCLK_OUT ; 
 int RF_DMA_EN ; 
 scalar_t__ ROCKCHIP_SPI_CTRLR0 ; 
 scalar_t__ ROCKCHIP_SPI_CTRLR1 ; 
 scalar_t__ ROCKCHIP_SPI_DMACR ; 
 scalar_t__ ROCKCHIP_SPI_DMARDLR ; 
 scalar_t__ ROCKCHIP_SPI_DMATDLR ; 
 scalar_t__ ROCKCHIP_SPI_RXFTLR ; 
 scalar_t__ ROCKCHIP_SPI_TXFTLR ; 
 int TF_DMA_EN ; 
 scalar_t__ WARN_ON (int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int,int,...) ; 
 int /*<<< orphan*/  spi_set_clk (struct rockchip_spi*,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void rockchip_spi_config(struct rockchip_spi *rs)
{
	u32 div = 0;
	u32 dmacr = 0;
	int rsd = 0;

	u32 cr0 = (CR0_BHT_8BIT << CR0_BHT_OFFSET)
		| (CR0_SSD_ONE << CR0_SSD_OFFSET)
		| (CR0_EM_BIG << CR0_EM_OFFSET);

	cr0 |= (rs->n_bytes << CR0_DFS_OFFSET);
	cr0 |= ((rs->mode & 0x3) << CR0_SCPH_OFFSET);
	cr0 |= (rs->tmode << CR0_XFM_OFFSET);
	cr0 |= (rs->type << CR0_FRF_OFFSET);

	if (rs->use_dma) {
		if (rs->tx)
			dmacr |= TF_DMA_EN;
		if (rs->rx)
			dmacr |= RF_DMA_EN;
	}

	if (WARN_ON(rs->speed > MAX_SCLK_OUT))
		rs->speed = MAX_SCLK_OUT;

	/* the minimum divisor is 2 */
	if (rs->max_freq < 2 * rs->speed) {
		clk_set_rate(rs->spiclk, 2 * rs->speed);
		rs->max_freq = clk_get_rate(rs->spiclk);
	}

	/* div doesn't support odd number */
	div = DIV_ROUND_UP(rs->max_freq, rs->speed);
	div = (div + 1) & 0xfffe;

	/* Rx sample delay is expressed in parent clock cycles (max 3) */
	rsd = DIV_ROUND_CLOSEST(rs->rsd_nsecs * (rs->max_freq >> 8),
				1000000000 >> 8);
	if (!rsd && rs->rsd_nsecs) {
		pr_warn_once("rockchip-spi: %u Hz are too slow to express %u ns delay\n",
			     rs->max_freq, rs->rsd_nsecs);
	} else if (rsd > 3) {
		rsd = 3;
		pr_warn_once("rockchip-spi: %u Hz are too fast to express %u ns delay, clamping at %u ns\n",
			     rs->max_freq, rs->rsd_nsecs,
			     rsd * 1000000000U / rs->max_freq);
	}
	cr0 |= rsd << CR0_RSD_OFFSET;

	writel_relaxed(cr0, rs->regs + ROCKCHIP_SPI_CTRLR0);

	if (rs->n_bytes == 1)
		writel_relaxed(rs->len - 1, rs->regs + ROCKCHIP_SPI_CTRLR1);
	else if (rs->n_bytes == 2)
		writel_relaxed((rs->len / 2) - 1, rs->regs + ROCKCHIP_SPI_CTRLR1);
	else
		writel_relaxed((rs->len * 2) - 1, rs->regs + ROCKCHIP_SPI_CTRLR1);

	writel_relaxed(rs->fifo_len / 2 - 1, rs->regs + ROCKCHIP_SPI_TXFTLR);
	writel_relaxed(rs->fifo_len / 2 - 1, rs->regs + ROCKCHIP_SPI_RXFTLR);

	writel_relaxed(0, rs->regs + ROCKCHIP_SPI_DMATDLR);
	writel_relaxed(0, rs->regs + ROCKCHIP_SPI_DMARDLR);
	writel_relaxed(dmacr, rs->regs + ROCKCHIP_SPI_DMACR);

	spi_set_clk(rs, div);

	dev_dbg(rs->dev, "cr0 0x%x, div %d\n", cr0, div);
}