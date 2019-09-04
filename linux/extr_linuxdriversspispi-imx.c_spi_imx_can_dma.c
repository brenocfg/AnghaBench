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
struct spi_transfer {unsigned int len; int /*<<< orphan*/  bits_per_word; } ;
struct spi_master {int /*<<< orphan*/  dma_rx; } ;
struct spi_imx_data {unsigned int wml; scalar_t__ dynamic_burst; TYPE_1__* devtype_data; scalar_t__ slave_mode; } ;
struct spi_device {int dummy; } ;
struct TYPE_2__ {int fifo_size; } ;

/* Variables and functions */
 unsigned int spi_imx_bytes_per_word (int /*<<< orphan*/ ) ; 
 struct spi_imx_data* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static bool spi_imx_can_dma(struct spi_master *master, struct spi_device *spi,
			 struct spi_transfer *transfer)
{
	struct spi_imx_data *spi_imx = spi_master_get_devdata(master);
	unsigned int bytes_per_word, i;

	if (!master->dma_rx)
		return false;

	if (spi_imx->slave_mode)
		return false;

	bytes_per_word = spi_imx_bytes_per_word(transfer->bits_per_word);

	for (i = spi_imx->devtype_data->fifo_size / 2; i > 0; i--) {
		if (!(transfer->len % (i * bytes_per_word)))
			break;
	}

	spi_imx->wml = i;
	spi_imx->dynamic_burst = 0;

	return true;
}