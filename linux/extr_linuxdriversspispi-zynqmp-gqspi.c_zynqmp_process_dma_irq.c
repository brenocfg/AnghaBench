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
struct zynqmp_qspi {int bytes_to_receive; int genfifoentry; scalar_t__ dma_rx_bytes; int /*<<< orphan*/  rxbuf; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int GQSPI_CFG_MODE_EN_MASK ; 
 int GQSPI_CFG_START_GEN_FIFO_MASK ; 
 int /*<<< orphan*/  GQSPI_CONFIG_OFST ; 
 int /*<<< orphan*/  GQSPI_GEN_FIFO_OFST ; 
 int GQSPI_IER_GENFIFOEMPTY_MASK ; 
 int /*<<< orphan*/  GQSPI_IER_OFST ; 
 int GQSPI_IER_RXEMPTY_MASK ; 
 int GQSPI_IER_RXNEMPTY_MASK ; 
 int /*<<< orphan*/  GQSPI_QSPIDMA_DST_I_DIS_OFST ; 
 int GQSPI_QSPIDMA_DST_I_EN_DONE_MASK ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int zynqmp_gqspi_read (struct zynqmp_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_gqspi_write (struct zynqmp_qspi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zynqmp_process_dma_irq(struct zynqmp_qspi *xqspi)
{
	u32 config_reg, genfifoentry;

	dma_unmap_single(xqspi->dev, xqspi->dma_addr,
				xqspi->dma_rx_bytes, DMA_FROM_DEVICE);
	xqspi->rxbuf += xqspi->dma_rx_bytes;
	xqspi->bytes_to_receive -= xqspi->dma_rx_bytes;
	xqspi->dma_rx_bytes = 0;

	/* Disabling the DMA interrupts */
	zynqmp_gqspi_write(xqspi, GQSPI_QSPIDMA_DST_I_DIS_OFST,
					GQSPI_QSPIDMA_DST_I_EN_DONE_MASK);

	if (xqspi->bytes_to_receive > 0) {
		/* Switch to IO mode,for remaining bytes to receive */
		config_reg = zynqmp_gqspi_read(xqspi, GQSPI_CONFIG_OFST);
		config_reg &= ~GQSPI_CFG_MODE_EN_MASK;
		zynqmp_gqspi_write(xqspi, GQSPI_CONFIG_OFST, config_reg);

		/* Initiate the transfer of remaining bytes */
		genfifoentry = xqspi->genfifoentry;
		genfifoentry |= xqspi->bytes_to_receive;
		zynqmp_gqspi_write(xqspi, GQSPI_GEN_FIFO_OFST, genfifoentry);

		/* Dummy generic FIFO entry */
		zynqmp_gqspi_write(xqspi, GQSPI_GEN_FIFO_OFST, 0x0);

		/* Manual start */
		zynqmp_gqspi_write(xqspi, GQSPI_CONFIG_OFST,
			(zynqmp_gqspi_read(xqspi, GQSPI_CONFIG_OFST) |
			GQSPI_CFG_START_GEN_FIFO_MASK));

		/* Enable the RX interrupts for IO mode */
		zynqmp_gqspi_write(xqspi, GQSPI_IER_OFST,
				GQSPI_IER_GENFIFOEMPTY_MASK |
				GQSPI_IER_RXNEMPTY_MASK |
				GQSPI_IER_RXEMPTY_MASK);
	}
}