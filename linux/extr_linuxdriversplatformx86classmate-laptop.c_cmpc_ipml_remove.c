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
struct ipml200_dev {scalar_t__ rf; int /*<<< orphan*/  bd; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (int /*<<< orphan*/ ) ; 
 struct ipml200_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ipml200_dev*) ; 
 int /*<<< orphan*/  rfkill_destroy (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_unregister (scalar_t__) ; 

__attribute__((used)) static int cmpc_ipml_remove(struct acpi_device *acpi)
{
	struct ipml200_dev *ipml;

	ipml = dev_get_drvdata(&acpi->dev);

	backlight_device_unregister(ipml->bd);

	if (ipml->rf) {
		rfkill_unregister(ipml->rf);
		rfkill_destroy(ipml->rf);
	}

	kfree(ipml);

	return 0;
}