#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; } ;
struct cmpc_accel {int /*<<< orphan*/  inputdev_state; int /*<<< orphan*/  g_select; int /*<<< orphan*/  sensitivity; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMPC_ACCEL_DEV_STATE_OPEN ; 
 int EIO ; 
 int /*<<< orphan*/  cmpc_accel_set_g_select_v4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpc_accel_set_sensitivity_v4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpc_start_accel_v4 (int /*<<< orphan*/ ) ; 
 struct cmpc_accel* dev_get_drvdata (TYPE_1__*) ; 
 struct acpi_device* to_acpi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmpc_accel_open_v4(struct input_dev *input)
{
	struct acpi_device *acpi;
	struct cmpc_accel *accel;

	acpi = to_acpi_device(input->dev.parent);
	accel = dev_get_drvdata(&input->dev);

	cmpc_accel_set_sensitivity_v4(acpi->handle, accel->sensitivity);
	cmpc_accel_set_g_select_v4(acpi->handle, accel->g_select);

	if (ACPI_SUCCESS(cmpc_start_accel_v4(acpi->handle))) {
		accel->inputdev_state = CMPC_ACCEL_DEV_STATE_OPEN;
		return 0;
	}
	return -EIO;
}