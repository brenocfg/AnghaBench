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
struct acpi_device {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_TABLET_MODE ; 
 int /*<<< orphan*/  cmpc_get_tablet (int /*<<< orphan*/ ,unsigned long long*) ; 
 struct input_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_report_switch (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void cmpc_tablet_handler(struct acpi_device *dev, u32 event)
{
	unsigned long long val = 0;
	struct input_dev *inputdev = dev_get_drvdata(&dev->dev);

	if (event == 0x81) {
		if (ACPI_SUCCESS(cmpc_get_tablet(dev->handle, &val))) {
			input_report_switch(inputdev, SW_TABLET_MODE, !val);
			input_sync(inputdev);
		}
	}
}