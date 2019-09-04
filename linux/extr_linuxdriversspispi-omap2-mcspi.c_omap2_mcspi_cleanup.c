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
struct spi_device {size_t chip_select; int /*<<< orphan*/  cs_gpio; TYPE_1__* master; struct omap2_mcspi_cs* controller_state; } ;
struct omap2_mcspi_dma {int /*<<< orphan*/ * dma_tx; int /*<<< orphan*/ * dma_rx; } ;
struct omap2_mcspi_cs {int /*<<< orphan*/  node; } ;
struct omap2_mcspi {struct omap2_mcspi_dma* dma_channels; } ;
struct TYPE_2__ {size_t num_chipselect; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct omap2_mcspi_cs*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct omap2_mcspi* spi_master_get_devdata (TYPE_1__*) ; 

__attribute__((used)) static void omap2_mcspi_cleanup(struct spi_device *spi)
{
	struct omap2_mcspi	*mcspi;
	struct omap2_mcspi_dma	*mcspi_dma;
	struct omap2_mcspi_cs	*cs;

	mcspi = spi_master_get_devdata(spi->master);

	if (spi->controller_state) {
		/* Unlink controller state from context save list */
		cs = spi->controller_state;
		list_del(&cs->node);

		kfree(cs);
	}

	if (spi->chip_select < spi->master->num_chipselect) {
		mcspi_dma = &mcspi->dma_channels[spi->chip_select];

		if (mcspi_dma->dma_rx) {
			dma_release_channel(mcspi_dma->dma_rx);
			mcspi_dma->dma_rx = NULL;
		}
		if (mcspi_dma->dma_tx) {
			dma_release_channel(mcspi_dma->dma_tx);
			mcspi_dma->dma_tx = NULL;
		}
	}

	if (gpio_is_valid(spi->cs_gpio))
		gpio_free(spi->cs_gpio);
}