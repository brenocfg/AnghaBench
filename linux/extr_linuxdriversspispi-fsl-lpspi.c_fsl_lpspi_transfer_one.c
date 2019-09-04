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
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;
struct fsl_lpspi_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  remain; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fsl_lpspi_read_rx_fifo (struct fsl_lpspi_data*) ; 
 int fsl_lpspi_txfifo_empty (struct fsl_lpspi_data*) ; 
 int /*<<< orphan*/  fsl_lpspi_write_tx_fifo (struct fsl_lpspi_data*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct fsl_lpspi_data* spi_master_get_devdata (struct spi_master*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_lpspi_transfer_one(struct spi_master *master,
				  struct spi_device *spi,
				  struct spi_transfer *t)
{
	struct fsl_lpspi_data *fsl_lpspi = spi_master_get_devdata(master);
	int ret;

	fsl_lpspi->tx_buf = t->tx_buf;
	fsl_lpspi->rx_buf = t->rx_buf;
	fsl_lpspi->remain = t->len;

	reinit_completion(&fsl_lpspi->xfer_done);
	fsl_lpspi_write_tx_fifo(fsl_lpspi);

	ret = wait_for_completion_timeout(&fsl_lpspi->xfer_done, HZ);
	if (!ret) {
		dev_dbg(fsl_lpspi->dev, "wait for completion timeout\n");
		return -ETIMEDOUT;
	}

	ret = fsl_lpspi_txfifo_empty(fsl_lpspi);
	if (ret)
		return ret;

	fsl_lpspi_read_rx_fifo(fsl_lpspi);

	return 0;
}