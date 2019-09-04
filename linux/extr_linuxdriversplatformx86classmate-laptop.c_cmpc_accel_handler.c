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
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpc_get_accel (int /*<<< orphan*/ ,unsigned char*,unsigned char*,unsigned char*) ; 
 struct input_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void cmpc_accel_handler(struct acpi_device *dev, u32 event)
{
	if (event == 0x81) {
		unsigned char x, y, z;
		acpi_status status;

		status = cmpc_get_accel(dev->handle, &x, &y, &z);
		if (ACPI_SUCCESS(status)) {
			struct input_dev *inputdev = dev_get_drvdata(&dev->dev);

			input_report_abs(inputdev, ABS_X, x);
			input_report_abs(inputdev, ABS_Y, y);
			input_report_abs(inputdev, ABS_Z, z);
			input_sync(inputdev);
		}
	}
}