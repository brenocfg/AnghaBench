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
struct ucsi_acpi {int /*<<< orphan*/  ucsi; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ucsi_acpi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  ucsi_acpi_notify ; 
 int /*<<< orphan*/  ucsi_unregister_ppm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucsi_acpi_remove(struct platform_device *pdev)
{
	struct ucsi_acpi *ua = platform_get_drvdata(pdev);

	ucsi_unregister_ppm(ua->ucsi);

	acpi_remove_notify_handler(ACPI_HANDLE(&pdev->dev), ACPI_DEVICE_NOTIFY,
				   ucsi_acpi_notify);

	return 0;
}