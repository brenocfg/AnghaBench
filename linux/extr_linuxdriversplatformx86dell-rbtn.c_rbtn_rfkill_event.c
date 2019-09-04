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
struct rbtn_data {scalar_t__ rfkill; } ;
struct acpi_device {struct rbtn_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  rbtn_rfkill_query (scalar_t__,struct acpi_device*) ; 

__attribute__((used)) static void rbtn_rfkill_event(struct acpi_device *device)
{
	struct rbtn_data *rbtn_data = device->driver_data;

	if (rbtn_data->rfkill)
		rbtn_rfkill_query(rbtn_data->rfkill, device);
}