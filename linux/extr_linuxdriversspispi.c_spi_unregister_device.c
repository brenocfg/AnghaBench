#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ of_node; } ;
struct spi_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_COMPANION (TYPE_1__*) ; 
 int /*<<< orphan*/  OF_POPULATED ; 
 int /*<<< orphan*/  acpi_device_clear_enumerated (scalar_t__) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  of_node_clear_flag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (scalar_t__) ; 

void spi_unregister_device(struct spi_device *spi)
{
	if (!spi)
		return;

	if (spi->dev.of_node) {
		of_node_clear_flag(spi->dev.of_node, OF_POPULATED);
		of_node_put(spi->dev.of_node);
	}
	if (ACPI_COMPANION(&spi->dev))
		acpi_device_clear_enumerated(ACPI_COMPANION(&spi->dev));
	device_unregister(&spi->dev);
}