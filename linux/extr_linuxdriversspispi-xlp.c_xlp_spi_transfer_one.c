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
struct xlp_spi_priv {int cmd_cont; int /*<<< orphan*/  dev; int /*<<< orphan*/  cs; } ;
struct spi_transfer {int dummy; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  chip_select; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct xlp_spi_priv* spi_master_get_devdata (struct spi_master*) ; 
 scalar_t__ spi_transfer_is_last (struct spi_master*,struct spi_transfer*) ; 
 scalar_t__ xlp_spi_txrx_bufs (struct xlp_spi_priv*,struct spi_transfer*) ; 

__attribute__((used)) static int xlp_spi_transfer_one(struct spi_master *master,
					struct spi_device *spi,
					struct spi_transfer *t)
{
	struct xlp_spi_priv *xspi = spi_master_get_devdata(master);
	int ret = 0;

	xspi->cs = spi->chip_select;
	xspi->dev = spi->dev;

	if (spi_transfer_is_last(master, t))
		xspi->cmd_cont = 0;
	else
		xspi->cmd_cont = 1;

	if (xlp_spi_txrx_bufs(xspi, t))
		ret = -EIO;

	spi_finalize_current_transfer(master);
	return ret;
}