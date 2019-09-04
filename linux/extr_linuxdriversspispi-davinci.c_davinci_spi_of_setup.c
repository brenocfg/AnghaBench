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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct spi_device {struct davinci_spi_config* controller_data; int /*<<< orphan*/  master; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct davinci_spi_config {int /*<<< orphan*/  io_type; scalar_t__ wdelay; } ;
struct davinci_spi {scalar_t__ dma_tx; scalar_t__ dma_rx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPI_IO_TYPE_DMA ; 
 struct davinci_spi_config davinci_spi_default_cfg ; 
 struct davinci_spi_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct davinci_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int davinci_spi_of_setup(struct spi_device *spi)
{
	struct davinci_spi_config *spicfg = spi->controller_data;
	struct device_node *np = spi->dev.of_node;
	struct davinci_spi *dspi = spi_master_get_devdata(spi->master);
	u32 prop;

	if (spicfg == NULL && np) {
		spicfg = kzalloc(sizeof(*spicfg), GFP_KERNEL);
		if (!spicfg)
			return -ENOMEM;
		*spicfg = davinci_spi_default_cfg;
		/* override with dt configured values */
		if (!of_property_read_u32(np, "ti,spi-wdelay", &prop))
			spicfg->wdelay = (u8)prop;
		spi->controller_data = spicfg;

		if (dspi->dma_rx && dspi->dma_tx)
			spicfg->io_type = SPI_IO_TYPE_DMA;
	}

	return 0;
}