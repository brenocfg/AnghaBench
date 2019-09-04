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
struct guid_block {int notify_id; } ;
struct wmi_block {TYPE_1__* acpi_device; struct guid_block gblock; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_OK ; 
 scalar_t__ acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static acpi_status wmi_method_enable(struct wmi_block *wblock, int enable)
{
	struct guid_block *block = NULL;
	char method[5];
	acpi_status status;
	acpi_handle handle;

	block = &wblock->gblock;
	handle = wblock->acpi_device->handle;

	snprintf(method, 5, "WE%02X", block->notify_id);
	status = acpi_execute_simple_method(handle, method, enable);

	if (status != AE_OK && status != AE_NOT_FOUND)
		return status;
	else
		return AE_OK;
}