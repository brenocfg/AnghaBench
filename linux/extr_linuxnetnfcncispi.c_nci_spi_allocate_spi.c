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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct nci_spi {unsigned int xfer_udelay; int /*<<< orphan*/  req_completion; struct nci_dev* ndev; struct spi_device* spi; scalar_t__ xfer_speed_hz; int /*<<< orphan*/  acknowledge_mode; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nci_spi* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

struct nci_spi *nci_spi_allocate_spi(struct spi_device *spi,
				     u8 acknowledge_mode, unsigned int delay,
				     struct nci_dev *ndev)
{
	struct nci_spi *nspi;

	nspi = devm_kzalloc(&spi->dev, sizeof(struct nci_spi), GFP_KERNEL);
	if (!nspi)
		return NULL;

	nspi->acknowledge_mode = acknowledge_mode;
	nspi->xfer_udelay = delay;
	/* Use controller max SPI speed by default */
	nspi->xfer_speed_hz = 0;
	nspi->spi = spi;
	nspi->ndev = ndev;
	init_completion(&nspi->req_completion);

	return nspi;
}