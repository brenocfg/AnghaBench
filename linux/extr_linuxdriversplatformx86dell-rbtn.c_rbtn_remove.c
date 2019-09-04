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
struct rbtn_data {int type; } ;
struct acpi_device {struct rbtn_data* driver_data; } ;

/* Variables and functions */
#define  RBTN_SLIDER 129 
#define  RBTN_TOGGLE 128 
 int /*<<< orphan*/  rbtn_acquire (struct acpi_device*,int) ; 
 int /*<<< orphan*/  rbtn_input_exit (struct rbtn_data*) ; 
 int /*<<< orphan*/  rbtn_rfkill_exit (struct acpi_device*) ; 

__attribute__((used)) static int rbtn_remove(struct acpi_device *device)
{
	struct rbtn_data *rbtn_data = device->driver_data;

	switch (rbtn_data->type) {
	case RBTN_TOGGLE:
		rbtn_input_exit(rbtn_data);
		break;
	case RBTN_SLIDER:
		rbtn_rfkill_exit(device);
		break;
	default:
		break;
	}

	rbtn_acquire(device, false);
	device->driver_data = NULL;

	return 0;
}