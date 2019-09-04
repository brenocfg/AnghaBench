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
struct tegra_slink_data {int tx_status; int rx_status; int /*<<< orphan*/  dev; int /*<<< orphan*/  xfer_completion; } ;
struct spi_transfer {int dummy; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SLINK_DMA_TIMEOUT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct tegra_slink_data* spi_master_get_devdata (struct spi_master*) ; 
 int tegra_slink_start_transfer_one (struct spi_device*,struct spi_transfer*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_slink_transfer_one(struct spi_master *master,
				    struct spi_device *spi,
				    struct spi_transfer *xfer)
{
	struct tegra_slink_data *tspi = spi_master_get_devdata(master);
	int ret;

	reinit_completion(&tspi->xfer_completion);
	ret = tegra_slink_start_transfer_one(spi, xfer);
	if (ret < 0) {
		dev_err(tspi->dev,
			"spi can not start transfer, err %d\n", ret);
		return ret;
	}

	ret = wait_for_completion_timeout(&tspi->xfer_completion,
					  SLINK_DMA_TIMEOUT);
	if (WARN_ON(ret == 0)) {
		dev_err(tspi->dev,
			"spi transfer timeout, err %d\n", ret);
		return -EIO;
	}

	if (tspi->tx_status)
		return tspi->tx_status;
	if (tspi->rx_status)
		return tspi->rx_status;

	return 0;
}