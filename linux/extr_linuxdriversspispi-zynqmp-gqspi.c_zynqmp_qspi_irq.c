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
struct zynqmp_qspi {scalar_t__ mode; scalar_t__ bytes_to_receive; scalar_t__ bytes_to_transfer; } ;
struct spi_master {int dummy; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  GQSPI_IDR_OFST ; 
 int GQSPI_IER_GENFIFOEMPTY_MASK ; 
 int GQSPI_IER_RXEMPTY_MASK ; 
 int /*<<< orphan*/  GQSPI_IMASK_OFST ; 
 int GQSPI_IRQ_MASK ; 
 int GQSPI_ISR_IDR_MASK ; 
 int /*<<< orphan*/  GQSPI_ISR_OFST ; 
 int GQSPI_ISR_TXNOT_FULL_MASK ; 
 scalar_t__ GQSPI_MODE_DMA ; 
 int GQSPI_QSPIDMA_DST_I_STS_DONE_MASK ; 
 int /*<<< orphan*/  GQSPI_QSPIDMA_DST_I_STS_OFST ; 
 int /*<<< orphan*/  GQSPI_RX_FIFO_FILL ; 
 int /*<<< orphan*/  GQSPI_TX_FIFO_FILL ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct zynqmp_qspi* spi_master_get_devdata (struct spi_master*) ; 
 int zynqmp_gqspi_read (struct zynqmp_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_gqspi_write (struct zynqmp_qspi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zynqmp_process_dma_irq (struct zynqmp_qspi*) ; 
 int /*<<< orphan*/  zynqmp_qspi_filltxfifo (struct zynqmp_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_qspi_readrxfifo (struct zynqmp_qspi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t zynqmp_qspi_irq(int irq, void *dev_id)
{
	struct spi_master *master = dev_id;
	struct zynqmp_qspi *xqspi = spi_master_get_devdata(master);
	int ret = IRQ_NONE;
	u32 status, mask, dma_status = 0;

	status = zynqmp_gqspi_read(xqspi, GQSPI_ISR_OFST);
	zynqmp_gqspi_write(xqspi, GQSPI_ISR_OFST, status);
	mask = (status & ~(zynqmp_gqspi_read(xqspi, GQSPI_IMASK_OFST)));

	/* Read and clear DMA status */
	if (xqspi->mode == GQSPI_MODE_DMA) {
		dma_status =
			zynqmp_gqspi_read(xqspi, GQSPI_QSPIDMA_DST_I_STS_OFST);
		zynqmp_gqspi_write(xqspi, GQSPI_QSPIDMA_DST_I_STS_OFST,
								dma_status);
	}

	if (mask & GQSPI_ISR_TXNOT_FULL_MASK) {
		zynqmp_qspi_filltxfifo(xqspi, GQSPI_TX_FIFO_FILL);
		ret = IRQ_HANDLED;
	}

	if (dma_status & GQSPI_QSPIDMA_DST_I_STS_DONE_MASK) {
		zynqmp_process_dma_irq(xqspi);
		ret = IRQ_HANDLED;
	} else if (!(mask & GQSPI_IER_RXEMPTY_MASK) &&
			(mask & GQSPI_IER_GENFIFOEMPTY_MASK)) {
		zynqmp_qspi_readrxfifo(xqspi, GQSPI_RX_FIFO_FILL);
		ret = IRQ_HANDLED;
	}

	if ((xqspi->bytes_to_receive == 0) && (xqspi->bytes_to_transfer == 0)
			&& ((status & GQSPI_IRQ_MASK) == GQSPI_IRQ_MASK)) {
		zynqmp_gqspi_write(xqspi, GQSPI_IDR_OFST, GQSPI_ISR_IDR_MASK);
		spi_finalize_current_transfer(master);
		ret = IRQ_HANDLED;
	}
	return ret;
}