#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct device* parent; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * type; } ;
struct TYPE_6__ {int setable; TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  object_id; } ;
struct wmi_block {int read_takes_no_args; TYPE_2__ dev; TYPE_1__ gblock; int /*<<< orphan*/  char_mutex; } ;
struct guid_block {int flags; int /*<<< orphan*/  guid; } ;
struct device {int dummy; } ;
struct acpi_device_info {scalar_t__ type; scalar_t__ param_count; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_METHOD ; 
 int ACPI_WMI_EVENT ; 
 int ACPI_WMI_METHOD ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_3__*) ; 
 int get_subobj_info (int /*<<< orphan*/ ,char*,struct acpi_device_info**) ; 
 int /*<<< orphan*/  kfree (struct acpi_device_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncat (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmi_bus_type ; 
 int /*<<< orphan*/  wmi_type_data ; 
 int /*<<< orphan*/  wmi_type_event ; 
 int /*<<< orphan*/  wmi_type_method ; 

__attribute__((used)) static int wmi_create_device(struct device *wmi_bus_dev,
			     const struct guid_block *gblock,
			     struct wmi_block *wblock,
			     struct acpi_device *device)
{
	struct acpi_device_info *info;
	char method[5];
	int result;

	if (gblock->flags & ACPI_WMI_EVENT) {
		wblock->dev.dev.type = &wmi_type_event;
		goto out_init;
	}

	if (gblock->flags & ACPI_WMI_METHOD) {
		wblock->dev.dev.type = &wmi_type_method;
		mutex_init(&wblock->char_mutex);
		goto out_init;
	}

	/*
	 * Data Block Query Control Method (WQxx by convention) is
	 * required per the WMI documentation. If it is not present,
	 * we ignore this data block.
	 */
	strcpy(method, "WQ");
	strncat(method, wblock->gblock.object_id, 2);
	result = get_subobj_info(device->handle, method, &info);

	if (result) {
		dev_warn(wmi_bus_dev,
			 "%s data block query control method not found\n",
			 method);
		return result;
	}

	wblock->dev.dev.type = &wmi_type_data;

	/*
	 * The Microsoft documentation specifically states:
	 *
	 *   Data blocks registered with only a single instance
	 *   can ignore the parameter.
	 *
	 * ACPICA will get mad at us if we call the method with the wrong number
	 * of arguments, so check what our method expects.  (On some Dell
	 * laptops, WQxx may not be a method at all.)
	 */
	if (info->type != ACPI_TYPE_METHOD || info->param_count == 0)
		wblock->read_takes_no_args = true;

	kfree(info);

	strcpy(method, "WS");
	strncat(method, wblock->gblock.object_id, 2);
	result = get_subobj_info(device->handle, method, NULL);

	if (result == 0)
		wblock->dev.setable = true;

 out_init:
	wblock->dev.dev.bus = &wmi_bus_type;
	wblock->dev.dev.parent = wmi_bus_dev;

	dev_set_name(&wblock->dev.dev, "%pUL", gblock->guid);

	device_initialize(&wblock->dev.dev);

	return 0;
}