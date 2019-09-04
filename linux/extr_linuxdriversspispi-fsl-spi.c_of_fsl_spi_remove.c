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
struct spi_master {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mpc8xxx_spi {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ TYPE_FSL ; 
 int /*<<< orphan*/  fsl_spi_cpm_free (struct mpc8xxx_spi*) ; 
 int /*<<< orphan*/  of_fsl_spi_free_chipselects (int /*<<< orphan*/ *) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 struct mpc8xxx_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int of_fsl_spi_remove(struct platform_device *ofdev)
{
	struct spi_master *master = platform_get_drvdata(ofdev);
	struct mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(master);

	fsl_spi_cpm_free(mpc8xxx_spi);
	if (mpc8xxx_spi->type == TYPE_FSL)
		of_fsl_spi_free_chipselects(&ofdev->dev);
	return 0;
}