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
struct asus_wireless_data {scalar_t__ wq; int /*<<< orphan*/  led; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct asus_wireless_data* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  devm_led_classdev_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asus_wireless_remove(struct acpi_device *adev)
{
	struct asus_wireless_data *data = acpi_driver_data(adev);

	if (data->wq) {
		devm_led_classdev_unregister(&adev->dev, &data->led);
		destroy_workqueue(data->wq);
	}
	return 0;
}