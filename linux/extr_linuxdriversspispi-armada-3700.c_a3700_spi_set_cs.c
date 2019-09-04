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
struct spi_device {int /*<<< orphan*/  chip_select; int /*<<< orphan*/  master; } ;
struct a3700_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  a3700_spi_activate_cs (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3700_spi_deactivate_cs (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 struct a3700_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a3700_spi_set_cs(struct spi_device *spi, bool enable)
{
	struct a3700_spi *a3700_spi = spi_master_get_devdata(spi->master);

	if (!enable)
		a3700_spi_activate_cs(a3700_spi, spi->chip_select);
	else
		a3700_spi_deactivate_cs(a3700_spi, spi->chip_select);
}