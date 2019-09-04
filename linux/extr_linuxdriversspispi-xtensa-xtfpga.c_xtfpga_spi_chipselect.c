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
struct xtfpga_spi {scalar_t__ data_sz; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct xtfpga_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xtfpga_spi_chipselect(struct spi_device *spi, int is_on)
{
	struct xtfpga_spi *xspi = spi_master_get_devdata(spi->master);

	WARN_ON(xspi->data_sz != 0);
	xspi->data_sz = 0;
}