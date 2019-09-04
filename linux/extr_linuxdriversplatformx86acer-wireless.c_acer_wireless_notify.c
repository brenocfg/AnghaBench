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
typedef  int u32 ;
struct input_dev {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_RFKILL ; 
 struct input_dev* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void acer_wireless_notify(struct acpi_device *adev, u32 event)
{
	struct input_dev *idev = acpi_driver_data(adev);

	dev_dbg(&adev->dev, "event=%#x\n", event);
	if (event != 0x80) {
		dev_notice(&adev->dev, "Unknown SMKB event: %#x\n", event);
		return;
	}
	input_report_key(idev, KEY_RFKILL, 1);
	input_report_key(idev, KEY_RFKILL, 0);
	input_sync(idev);
}