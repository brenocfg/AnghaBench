#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct spi_transfer {int* rx_buf; int len; int* tx_buf; int tx_dma; int rx_dma; } ;
struct spi_master {TYPE_1__* cur_msg; int /*<<< orphan*/  (* can_dma ) (struct spi_master*,int /*<<< orphan*/ ,struct spi_transfer*) ;} ;
struct mtk_spi {int xfer_len; scalar_t__ tx_sgl_len; scalar_t__ rx_sgl_len; scalar_t__ base; void* rx_sgl; void* tx_sgl; int /*<<< orphan*/  state; struct spi_transfer* cur_transfer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MTK_SPI_IDLE ; 
 int /*<<< orphan*/  MTK_SPI_MAX_FIFO_SIZE ; 
 int /*<<< orphan*/  MTK_SPI_PAUSED ; 
 int MTK_SPI_PAUSE_INT_STATUS ; 
 scalar_t__ SPI_CMD_REG ; 
 int SPI_CMD_RX_DMA ; 
 int SPI_CMD_TX_DMA ; 
 scalar_t__ SPI_RX_DATA_REG ; 
 scalar_t__ SPI_STATUS0_REG ; 
 scalar_t__ SPI_TX_DATA_REG ; 
 int /*<<< orphan*/  ioread32_rep (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  iowrite32_rep (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_spi_enable_transfer (struct spi_master*) ; 
 int /*<<< orphan*/  mtk_spi_setup_dma_addr (struct spi_master*,struct spi_transfer*) ; 
 int /*<<< orphan*/  mtk_spi_setup_packet (struct spi_master*) ; 
 int /*<<< orphan*/  mtk_spi_update_mdata_len (struct spi_master*) ; 
 int readl (scalar_t__) ; 
 void* sg_dma_address (void*) ; 
 void* sg_dma_len (void*) ; 
 void* sg_next (void*) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct mtk_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  stub1 (struct spi_master*,int /*<<< orphan*/ ,struct spi_transfer*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mtk_spi_interrupt(int irq, void *dev_id)
{
	u32 cmd, reg_val, cnt, remainder;
	struct spi_master *master = dev_id;
	struct mtk_spi *mdata = spi_master_get_devdata(master);
	struct spi_transfer *trans = mdata->cur_transfer;

	reg_val = readl(mdata->base + SPI_STATUS0_REG);
	if (reg_val & MTK_SPI_PAUSE_INT_STATUS)
		mdata->state = MTK_SPI_PAUSED;
	else
		mdata->state = MTK_SPI_IDLE;

	if (!master->can_dma(master, master->cur_msg->spi, trans)) {
		if (trans->rx_buf) {
			cnt = mdata->xfer_len / 4;
			ioread32_rep(mdata->base + SPI_RX_DATA_REG,
				     trans->rx_buf, cnt);
			remainder = mdata->xfer_len % 4;
			if (remainder > 0) {
				reg_val = readl(mdata->base + SPI_RX_DATA_REG);
				memcpy(trans->rx_buf + (cnt * 4),
					&reg_val, remainder);
			}
		}

		trans->len -= mdata->xfer_len;
		if (!trans->len) {
			spi_finalize_current_transfer(master);
			return IRQ_HANDLED;
		}

		if (trans->tx_buf)
			trans->tx_buf += mdata->xfer_len;
		if (trans->rx_buf)
			trans->rx_buf += mdata->xfer_len;

		mdata->xfer_len = min(MTK_SPI_MAX_FIFO_SIZE, trans->len);
		mtk_spi_setup_packet(master);

		cnt = trans->len / 4;
		iowrite32_rep(mdata->base + SPI_TX_DATA_REG, trans->tx_buf, cnt);

		remainder = trans->len % 4;
		if (remainder > 0) {
			reg_val = 0;
			memcpy(&reg_val, trans->tx_buf + (cnt * 4), remainder);
			writel(reg_val, mdata->base + SPI_TX_DATA_REG);
		}

		mtk_spi_enable_transfer(master);

		return IRQ_HANDLED;
	}

	if (mdata->tx_sgl)
		trans->tx_dma += mdata->xfer_len;
	if (mdata->rx_sgl)
		trans->rx_dma += mdata->xfer_len;

	if (mdata->tx_sgl && (mdata->tx_sgl_len == 0)) {
		mdata->tx_sgl = sg_next(mdata->tx_sgl);
		if (mdata->tx_sgl) {
			trans->tx_dma = sg_dma_address(mdata->tx_sgl);
			mdata->tx_sgl_len = sg_dma_len(mdata->tx_sgl);
		}
	}
	if (mdata->rx_sgl && (mdata->rx_sgl_len == 0)) {
		mdata->rx_sgl = sg_next(mdata->rx_sgl);
		if (mdata->rx_sgl) {
			trans->rx_dma = sg_dma_address(mdata->rx_sgl);
			mdata->rx_sgl_len = sg_dma_len(mdata->rx_sgl);
		}
	}

	if (!mdata->tx_sgl && !mdata->rx_sgl) {
		/* spi disable dma */
		cmd = readl(mdata->base + SPI_CMD_REG);
		cmd &= ~SPI_CMD_TX_DMA;
		cmd &= ~SPI_CMD_RX_DMA;
		writel(cmd, mdata->base + SPI_CMD_REG);

		spi_finalize_current_transfer(master);
		return IRQ_HANDLED;
	}

	mtk_spi_update_mdata_len(master);
	mtk_spi_setup_packet(master);
	mtk_spi_setup_dma_addr(master, trans);
	mtk_spi_enable_transfer(master);

	return IRQ_HANDLED;
}