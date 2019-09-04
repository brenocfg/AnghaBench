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
struct spi_mpc8xxx_cs {int dummy; } ;
struct spi_device {int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  master; } ;
struct mpc8xxx_spi {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ TYPE_GRLIB ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct spi_mpc8xxx_cs*) ; 
 struct spi_mpc8xxx_cs* spi_get_ctldata (struct spi_device*) ; 
 struct mpc8xxx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_spi_cleanup(struct spi_device *spi)
{
	struct mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(spi->master);
	struct spi_mpc8xxx_cs *cs = spi_get_ctldata(spi);

	if (mpc8xxx_spi->type == TYPE_GRLIB && gpio_is_valid(spi->cs_gpio))
		gpio_free(spi->cs_gpio);

	kfree(cs);
	spi_set_ctldata(spi, NULL);
}