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
struct spi_device {int /*<<< orphan*/  chip_select; TYPE_1__* controller; int /*<<< orphan*/  dev; } ;
struct acpi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_dev_name (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void spi_dev_set_name(struct spi_device *spi)
{
	struct acpi_device *adev = ACPI_COMPANION(&spi->dev);

	if (adev) {
		dev_set_name(&spi->dev, "spi-%s", acpi_dev_name(adev));
		return;
	}

	dev_set_name(&spi->dev, "%s.%u", dev_name(&spi->controller->dev),
		     spi->chip_select);
}