#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct spi_transfer {scalar_t__ len; int rx_buf; int bits_per_word; int speed_hz; scalar_t__ tx_buf; scalar_t__ tx_dma; scalar_t__ rx_dma; } ;
struct spi_message {TYPE_2__* spi; scalar_t__ is_dma_mapped; } ;
struct spi_device {int dummy; } ;
struct spi_controller {int max_speed_hz; scalar_t__ cur_msg_mapped; scalar_t__ (* can_dma ) (struct spi_controller*,TYPE_2__*,struct spi_transfer*) ;struct spi_message* cur_msg; } ;
struct driver_data {int n_bytes; int rx; int rx_end; scalar_t__ write; scalar_t__ read; int dma_cr1; int clear_sr; int int_cr1; int /*<<< orphan*/  transfer_handler; void* tx; void* tx_end; TYPE_1__* pdev; } ;
struct chip_data {int dma_threshold; int dma_burst_size; int n_bytes; scalar_t__ write; scalar_t__ read; int cr1; int threshold; int lpss_rx_threshold; int lpss_tx_threshold; int dds_rate; int timeout; scalar_t__ enable_dma; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDS_RATE ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ MAX_DMA_LEN ; 
 int /*<<< orphan*/  SSCR0 ; 
 int SSCR0_SCR (int) ; 
 int SSCR0_SSE ; 
 int /*<<< orphan*/  SSCR1 ; 
 int /*<<< orphan*/  SSIRF ; 
 int /*<<< orphan*/  SSITF ; 
 int /*<<< orphan*/  SSSR ; 
 int /*<<< orphan*/  SSTO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  interrupt_transfer ; 
 scalar_t__ is_lpss_ssp (struct driver_data*) ; 
 scalar_t__ is_quark_x1000_ssp (struct driver_data*) ; 
 scalar_t__ null_reader ; 
 scalar_t__ null_writer ; 
 int /*<<< orphan*/  pxa25x_ssp_comp (struct driver_data*) ; 
 int pxa2xx_configure_sscr0 (struct driver_data*,int,int) ; 
 int pxa2xx_spi_dma_prepare (struct driver_data*,struct spi_transfer*) ; 
 int /*<<< orphan*/  pxa2xx_spi_dma_start (struct driver_data*) ; 
 int /*<<< orphan*/  pxa2xx_spi_dma_transfer ; 
 scalar_t__ pxa2xx_spi_flush (struct driver_data*) ; 
 int pxa2xx_spi_get_ssrc1_change_mask (struct driver_data*) ; 
 int pxa2xx_spi_read (struct driver_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ pxa2xx_spi_set_dma_burst_and_threshold (struct chip_data*,TYPE_2__*,int,int*,int*) ; 
 int /*<<< orphan*/  pxa2xx_spi_write (struct driver_data*,int /*<<< orphan*/ ,int) ; 
 int pxa2xx_ssp_get_clk_div (struct driver_data*,int) ; 
 struct driver_data* spi_controller_get_devdata (struct spi_controller*) ; 
 struct chip_data* spi_get_ctldata (TYPE_2__*) ; 
 scalar_t__ stub1 (struct spi_controller*,TYPE_2__*,struct spi_transfer*) ; 
 scalar_t__ u16_reader ; 
 scalar_t__ u16_writer ; 
 scalar_t__ u32_reader ; 
 scalar_t__ u32_writer ; 
 scalar_t__ u8_reader ; 
 scalar_t__ u8_writer ; 
 int /*<<< orphan*/  write_SSSR_CS (struct driver_data*,int) ; 

__attribute__((used)) static int pxa2xx_spi_transfer_one(struct spi_controller *master,
				   struct spi_device *spi,
				   struct spi_transfer *transfer)
{
	struct driver_data *drv_data = spi_controller_get_devdata(master);
	struct spi_message *message = master->cur_msg;
	struct chip_data *chip = spi_get_ctldata(message->spi);
	u32 dma_thresh = chip->dma_threshold;
	u32 dma_burst = chip->dma_burst_size;
	u32 change_mask = pxa2xx_spi_get_ssrc1_change_mask(drv_data);
	u32 clk_div;
	u8 bits;
	u32 speed;
	u32 cr0;
	u32 cr1;
	int err;
	int dma_mapped;

	/* Check if we can DMA this transfer */
	if (transfer->len > MAX_DMA_LEN && chip->enable_dma) {

		/* reject already-mapped transfers; PIO won't always work */
		if (message->is_dma_mapped
				|| transfer->rx_dma || transfer->tx_dma) {
			dev_err(&drv_data->pdev->dev,
				"Mapped transfer length of %u is greater than %d\n",
				transfer->len, MAX_DMA_LEN);
			return -EINVAL;
		}

		/* warn ... we force this to PIO mode */
		dev_warn_ratelimited(&message->spi->dev,
				     "DMA disabled for transfer length %ld greater than %d\n",
				     (long)transfer->len, MAX_DMA_LEN);
	}

	/* Setup the transfer state based on the type of transfer */
	if (pxa2xx_spi_flush(drv_data) == 0) {
		dev_err(&drv_data->pdev->dev, "Flush failed\n");
		return -EIO;
	}
	drv_data->n_bytes = chip->n_bytes;
	drv_data->tx = (void *)transfer->tx_buf;
	drv_data->tx_end = drv_data->tx + transfer->len;
	drv_data->rx = transfer->rx_buf;
	drv_data->rx_end = drv_data->rx + transfer->len;
	drv_data->write = drv_data->tx ? chip->write : null_writer;
	drv_data->read = drv_data->rx ? chip->read : null_reader;

	/* Change speed and bit per word on a per transfer */
	bits = transfer->bits_per_word;
	speed = transfer->speed_hz;

	clk_div = pxa2xx_ssp_get_clk_div(drv_data, speed);

	if (bits <= 8) {
		drv_data->n_bytes = 1;
		drv_data->read = drv_data->read != null_reader ?
					u8_reader : null_reader;
		drv_data->write = drv_data->write != null_writer ?
					u8_writer : null_writer;
	} else if (bits <= 16) {
		drv_data->n_bytes = 2;
		drv_data->read = drv_data->read != null_reader ?
					u16_reader : null_reader;
		drv_data->write = drv_data->write != null_writer ?
					u16_writer : null_writer;
	} else if (bits <= 32) {
		drv_data->n_bytes = 4;
		drv_data->read = drv_data->read != null_reader ?
					u32_reader : null_reader;
		drv_data->write = drv_data->write != null_writer ?
					u32_writer : null_writer;
	}
	/*
	 * if bits/word is changed in dma mode, then must check the
	 * thresholds and burst also
	 */
	if (chip->enable_dma) {
		if (pxa2xx_spi_set_dma_burst_and_threshold(chip,
						message->spi,
						bits, &dma_burst,
						&dma_thresh))
			dev_warn_ratelimited(&message->spi->dev,
					     "DMA burst size reduced to match bits_per_word\n");
	}

	dma_mapped = master->can_dma &&
		     master->can_dma(master, message->spi, transfer) &&
		     master->cur_msg_mapped;
	if (dma_mapped) {

		/* Ensure we have the correct interrupt handler */
		drv_data->transfer_handler = pxa2xx_spi_dma_transfer;

		err = pxa2xx_spi_dma_prepare(drv_data, transfer);
		if (err)
			return err;

		/* Clear status and start DMA engine */
		cr1 = chip->cr1 | dma_thresh | drv_data->dma_cr1;
		pxa2xx_spi_write(drv_data, SSSR, drv_data->clear_sr);

		pxa2xx_spi_dma_start(drv_data);
	} else {
		/* Ensure we have the correct interrupt handler	*/
		drv_data->transfer_handler = interrupt_transfer;

		/* Clear status  */
		cr1 = chip->cr1 | chip->threshold | drv_data->int_cr1;
		write_SSSR_CS(drv_data, drv_data->clear_sr);
	}

	/* NOTE:  PXA25x_SSP _could_ use external clocking ... */
	cr0 = pxa2xx_configure_sscr0(drv_data, clk_div, bits);
	if (!pxa25x_ssp_comp(drv_data))
		dev_dbg(&message->spi->dev, "%u Hz actual, %s\n",
			master->max_speed_hz
				/ (1 + ((cr0 & SSCR0_SCR(0xfff)) >> 8)),
			dma_mapped ? "DMA" : "PIO");
	else
		dev_dbg(&message->spi->dev, "%u Hz actual, %s\n",
			master->max_speed_hz / 2
				/ (1 + ((cr0 & SSCR0_SCR(0x0ff)) >> 8)),
			dma_mapped ? "DMA" : "PIO");

	if (is_lpss_ssp(drv_data)) {
		if ((pxa2xx_spi_read(drv_data, SSIRF) & 0xff)
		    != chip->lpss_rx_threshold)
			pxa2xx_spi_write(drv_data, SSIRF,
					 chip->lpss_rx_threshold);
		if ((pxa2xx_spi_read(drv_data, SSITF) & 0xffff)
		    != chip->lpss_tx_threshold)
			pxa2xx_spi_write(drv_data, SSITF,
					 chip->lpss_tx_threshold);
	}

	if (is_quark_x1000_ssp(drv_data) &&
	    (pxa2xx_spi_read(drv_data, DDS_RATE) != chip->dds_rate))
		pxa2xx_spi_write(drv_data, DDS_RATE, chip->dds_rate);

	/* see if we need to reload the config registers */
	if ((pxa2xx_spi_read(drv_data, SSCR0) != cr0)
	    || (pxa2xx_spi_read(drv_data, SSCR1) & change_mask)
	    != (cr1 & change_mask)) {
		/* stop the SSP, and update the other bits */
		pxa2xx_spi_write(drv_data, SSCR0, cr0 & ~SSCR0_SSE);
		if (!pxa25x_ssp_comp(drv_data))
			pxa2xx_spi_write(drv_data, SSTO, chip->timeout);
		/* first set CR1 without interrupt and service enables */
		pxa2xx_spi_write(drv_data, SSCR1, cr1 & change_mask);
		/* restart the SSP */
		pxa2xx_spi_write(drv_data, SSCR0, cr0);

	} else {
		if (!pxa25x_ssp_comp(drv_data))
			pxa2xx_spi_write(drv_data, SSTO, chip->timeout);
	}

	/*
	 * Release the data by enabling service requests and interrupts,
	 * without changing any mode bits
	 */
	pxa2xx_spi_write(drv_data, SSCR1, cr1);

	return 1;
}