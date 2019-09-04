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
struct input_dev {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct input_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 

__attribute__((used)) static int cmpc_remove_acpi_notify_device(struct acpi_device *acpi)
{
	struct input_dev *inputdev = dev_get_drvdata(&acpi->dev);
	input_unregister_device(inputdev);
	return 0;
}