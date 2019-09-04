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
struct rbtn_data {int type; scalar_t__ suspended; } ;
struct acpi_device {int /*<<< orphan*/  dev; struct rbtn_data* driver_data; } ;

/* Variables and functions */
#define  RBTN_SLIDER 129 
#define  RBTN_TOGGLE 128 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int,struct acpi_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  rbtn_chain_head ; 
 int /*<<< orphan*/  rbtn_input_event (struct rbtn_data*) ; 
 int /*<<< orphan*/  rbtn_rfkill_event (struct acpi_device*) ; 

__attribute__((used)) static void rbtn_notify(struct acpi_device *device, u32 event)
{
	struct rbtn_data *rbtn_data = device->driver_data;

	/*
	 * Some BIOSes send a notification at resume.
	 * Ignore it to prevent unwanted input events.
	 */
	if (rbtn_data->suspended) {
		dev_dbg(&device->dev, "ACPI notification ignored\n");
		return;
	}

	if (event != 0x80) {
		dev_info(&device->dev, "Received unknown event (0x%x)\n",
			 event);
		return;
	}

	switch (rbtn_data->type) {
	case RBTN_TOGGLE:
		rbtn_input_event(rbtn_data);
		break;
	case RBTN_SLIDER:
		rbtn_rfkill_event(device);
		atomic_notifier_call_chain(&rbtn_chain_head, event, device);
		break;
	default:
		break;
	}
}