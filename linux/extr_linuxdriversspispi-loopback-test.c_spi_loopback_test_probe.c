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
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_LOOP ; 
 int /*<<< orphan*/  SPI_NO_CS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ loop_req ; 
 scalar_t__ no_cs ; 
 int spi_setup (struct spi_device*) ; 
 int spi_test_run_tests (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_tests ; 

__attribute__((used)) static int spi_loopback_test_probe(struct spi_device *spi)
{
	int ret;

	if (loop_req || no_cs) {
		spi->mode |= loop_req ? SPI_LOOP : 0;
		spi->mode |= no_cs ? SPI_NO_CS : 0;
		ret = spi_setup(spi);
		if (ret) {
			dev_err(&spi->dev, "SPI setup with SPI_LOOP or SPI_NO_CS failed (%d)\n",
				ret);
			return ret;
		}
	}

	dev_info(&spi->dev, "Executing spi-loopback-tests\n");

	ret = spi_test_run_tests(spi, spi_tests);

	dev_info(&spi->dev, "Finished spi-loopback-tests with return: %i\n",
		 ret);

	return ret;
}