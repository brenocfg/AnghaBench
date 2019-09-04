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
struct txx9spi {int /*<<< orphan*/  lock; } ;
struct spi_device {int max_speed_hz; int mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int EINVAL ; 
 int NSEC_PER_SEC ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 struct txx9spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txx9spi_cs_func (struct spi_device*,struct txx9spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int txx9spi_setup(struct spi_device *spi)
{
	struct txx9spi *c = spi_master_get_devdata(spi->master);

	if (!spi->max_speed_hz)
		return -EINVAL;

	if (gpio_direction_output(spi->chip_select,
			!(spi->mode & SPI_CS_HIGH))) {
		dev_err(&spi->dev, "Cannot setup GPIO for chipselect.\n");
		return -EINVAL;
	}

	/* deselect chip */
	spin_lock(&c->lock);
	txx9spi_cs_func(spi, c, 0, (NSEC_PER_SEC / 2) / spi->max_speed_hz);
	spin_unlock(&c->lock);

	return 0;
}