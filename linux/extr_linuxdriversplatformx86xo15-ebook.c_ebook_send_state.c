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
struct ebook_switch {int /*<<< orphan*/  input; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  SW_TABLET_MODE ; 
 struct ebook_switch* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ebook_send_state(struct acpi_device *device)
{
	struct ebook_switch *button = acpi_driver_data(device);
	unsigned long long state;
	acpi_status status;

	status = acpi_evaluate_integer(device->handle, "EBK", NULL, &state);
	if (ACPI_FAILURE(status))
		return -EIO;

	/* input layer checks if event is redundant */
	input_report_switch(button->input, SW_TABLET_MODE, !state);
	input_sync(button->input);
	return 0;
}