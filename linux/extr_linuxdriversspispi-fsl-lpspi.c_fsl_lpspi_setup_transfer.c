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
struct spi_transfer {int bits_per_word; scalar_t__ speed_hz; } ;
struct spi_device {int bits_per_word; scalar_t__ max_speed_hz; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  mode; int /*<<< orphan*/  master; } ;
struct TYPE_2__ {int bpw; scalar_t__ speed_hz; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  mode; } ;
struct fsl_lpspi_data {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_lpspi_buf_rx_u16 ; 
 int /*<<< orphan*/  fsl_lpspi_buf_rx_u32 ; 
 int /*<<< orphan*/  fsl_lpspi_buf_rx_u8 ; 
 int /*<<< orphan*/  fsl_lpspi_buf_tx_u16 ; 
 int /*<<< orphan*/  fsl_lpspi_buf_tx_u32 ; 
 int /*<<< orphan*/  fsl_lpspi_buf_tx_u8 ; 
 int /*<<< orphan*/  fsl_lpspi_config (struct fsl_lpspi_data*) ; 
 struct fsl_lpspi_data* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_lpspi_setup_transfer(struct spi_device *spi,
				     struct spi_transfer *t)
{
	struct fsl_lpspi_data *fsl_lpspi = spi_master_get_devdata(spi->master);

	fsl_lpspi->config.mode = spi->mode;
	fsl_lpspi->config.bpw = t ? t->bits_per_word : spi->bits_per_word;
	fsl_lpspi->config.speed_hz = t ? t->speed_hz : spi->max_speed_hz;
	fsl_lpspi->config.chip_select = spi->chip_select;

	if (!fsl_lpspi->config.speed_hz)
		fsl_lpspi->config.speed_hz = spi->max_speed_hz;
	if (!fsl_lpspi->config.bpw)
		fsl_lpspi->config.bpw = spi->bits_per_word;

	/* Initialize the functions for transfer */
	if (fsl_lpspi->config.bpw <= 8) {
		fsl_lpspi->rx = fsl_lpspi_buf_rx_u8;
		fsl_lpspi->tx = fsl_lpspi_buf_tx_u8;
	} else if (fsl_lpspi->config.bpw <= 16) {
		fsl_lpspi->rx = fsl_lpspi_buf_rx_u16;
		fsl_lpspi->tx = fsl_lpspi_buf_tx_u16;
	} else {
		fsl_lpspi->rx = fsl_lpspi_buf_rx_u32;
		fsl_lpspi->tx = fsl_lpspi_buf_tx_u32;
	}

	fsl_lpspi_config(fsl_lpspi);
}