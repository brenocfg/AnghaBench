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
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  notify_handler ; 

__attribute__((used)) static int intel_vbtn_remove(struct platform_device *device)
{
	acpi_handle handle = ACPI_HANDLE(&device->dev);

	device_init_wakeup(&device->dev, false);
	acpi_remove_notify_handler(handle, ACPI_DEVICE_NOTIFY, notify_handler);

	/*
	 * Even if we failed to shut off the event stream, we can still
	 * safely detach from the device.
	 */
	return 0;
}