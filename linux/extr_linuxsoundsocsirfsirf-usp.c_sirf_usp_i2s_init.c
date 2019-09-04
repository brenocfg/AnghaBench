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
struct sirf_usp {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int RX_FIFO_HC (int) ; 
 int RX_FIFO_LC (int) ; 
 int RX_FIFO_SC (int) ; 
 int TX_FIFO_HC (int) ; 
 int TX_FIFO_LC (int) ; 
 int TX_FIFO_SC (int) ; 
 int USP_CLOCK_MODE_SLAVE ; 
 int USP_EN ; 
 int /*<<< orphan*/  USP_MODE1 ; 
 int /*<<< orphan*/  USP_MODE2 ; 
 int USP_RFS_ACT_LEVEL_LOGIC1 ; 
 int USP_RFS_CLK_SLAVE_MODE ; 
 int /*<<< orphan*/  USP_RISC_DSP_MODE ; 
 int /*<<< orphan*/  USP_RISC_DSP_SEL ; 
 int USP_RXD_DELAY_LEN_OFFSET ; 
 int /*<<< orphan*/  USP_RX_DMA_IO_CTRL ; 
 int /*<<< orphan*/  USP_RX_DMA_IO_LEN ; 
 int /*<<< orphan*/  USP_RX_FIFO_CTRL ; 
 int /*<<< orphan*/  USP_RX_FIFO_LEVEL_CHK ; 
 int USP_RX_FIFO_THD_OFFSET ; 
 int USP_RX_FIFO_THRESHOLD ; 
 int USP_RX_FIFO_WIDTH_OFFSET ; 
 int USP_SYNC_MODE ; 
 int USP_TFS_ACT_LEVEL_LOGIC1 ; 
 int USP_TFS_CLK_SLAVE_MODE ; 
 int USP_TXD_ACT_EDGE_FALLING ; 
 int USP_TXD_DELAY_LEN_OFFSET ; 
 int /*<<< orphan*/  USP_TX_DMA_IO_CTRL ; 
 int /*<<< orphan*/  USP_TX_DMA_IO_LEN ; 
 int /*<<< orphan*/  USP_TX_FIFO_CTRL ; 
 int /*<<< orphan*/  USP_TX_FIFO_LEVEL_CHK ; 
 int USP_TX_FIFO_THD_OFFSET ; 
 int USP_TX_FIFO_THRESHOLD ; 
 int USP_TX_FIFO_WIDTH_OFFSET ; 
 int USP_TX_RX_FIFO_WIDTH_DWORD ; 
 int USP_TX_UFLOW_REPEAT_ZERO ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sirf_usp_i2s_init(struct sirf_usp *usp)
{
	/* Configure RISC mode */
	regmap_update_bits(usp->regmap, USP_RISC_DSP_MODE,
		USP_RISC_DSP_SEL, ~USP_RISC_DSP_SEL);

	/*
	 * Configure DMA IO Length register
	 * Set no limit, USP can receive data continuously until it is diabled
	 */
	regmap_write(usp->regmap, USP_TX_DMA_IO_LEN, 0);
	regmap_write(usp->regmap, USP_RX_DMA_IO_LEN, 0);

	/* Configure Mode2 register */
	regmap_write(usp->regmap, USP_MODE2, (1 << USP_RXD_DELAY_LEN_OFFSET) |
		(0 << USP_TXD_DELAY_LEN_OFFSET) |
		USP_TFS_CLK_SLAVE_MODE | USP_RFS_CLK_SLAVE_MODE);

	/* Configure Mode1 register */
	regmap_write(usp->regmap, USP_MODE1,
		USP_SYNC_MODE | USP_EN | USP_TXD_ACT_EDGE_FALLING |
		USP_RFS_ACT_LEVEL_LOGIC1 | USP_TFS_ACT_LEVEL_LOGIC1 |
		USP_TX_UFLOW_REPEAT_ZERO | USP_CLOCK_MODE_SLAVE);

	/* Configure RX DMA IO Control register */
	regmap_write(usp->regmap, USP_RX_DMA_IO_CTRL, 0);

	/* Congiure RX FIFO Control register */
	regmap_write(usp->regmap, USP_RX_FIFO_CTRL,
		(USP_RX_FIFO_THRESHOLD << USP_RX_FIFO_THD_OFFSET) |
		(USP_TX_RX_FIFO_WIDTH_DWORD << USP_RX_FIFO_WIDTH_OFFSET));

	/* Congiure RX FIFO Level Check register */
	regmap_write(usp->regmap, USP_RX_FIFO_LEVEL_CHK,
		RX_FIFO_SC(0x04) | RX_FIFO_LC(0x0E) | RX_FIFO_HC(0x1B));

	/* Configure TX DMA IO Control register*/
	regmap_write(usp->regmap, USP_TX_DMA_IO_CTRL, 0);

	/* Configure TX FIFO Control register */
	regmap_write(usp->regmap, USP_TX_FIFO_CTRL,
		(USP_TX_FIFO_THRESHOLD << USP_TX_FIFO_THD_OFFSET) |
		(USP_TX_RX_FIFO_WIDTH_DWORD << USP_TX_FIFO_WIDTH_OFFSET));
	/* Congiure TX FIFO Level Check register */
	regmap_write(usp->regmap, USP_TX_FIFO_LEVEL_CHK,
		TX_FIFO_SC(0x1B) | TX_FIFO_LC(0x0E) | TX_FIFO_HC(0x04));
}