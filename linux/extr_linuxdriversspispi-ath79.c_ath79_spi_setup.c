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
struct spi_device {int /*<<< orphan*/  controller_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath79_spi_cleanup_cs (struct spi_device*) ; 
 int ath79_spi_setup_cs (struct spi_device*) ; 
 int spi_bitbang_setup (struct spi_device*) ; 

__attribute__((used)) static int ath79_spi_setup(struct spi_device *spi)
{
	int status = 0;

	if (!spi->controller_state) {
		status = ath79_spi_setup_cs(spi);
		if (status)
			return status;
	}

	status = spi_bitbang_setup(spi);
	if (status && !spi->controller_state)
		ath79_spi_cleanup_cs(spi);

	return status;
}