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
struct smo8800_device {int /*<<< orphan*/  miscdev; int /*<<< orphan*/  irq; } ;
struct acpi_device {int /*<<< orphan*/  dev; struct smo8800_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct smo8800_device*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smo8800_remove(struct acpi_device *device)
{
	struct smo8800_device *smo8800 = device->driver_data;

	free_irq(smo8800->irq, smo8800);
	misc_deregister(&smo8800->miscdev);
	dev_dbg(&device->dev, "device /dev/freefall unregistered\n");
	return 0;
}