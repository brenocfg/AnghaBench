#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ResourceOrder; int /*<<< orphan*/  SystemLevel; } ;
union acpi_object {TYPE_2__ PowerResource; } ;
struct acpi_power_resource {int /*<<< orphan*/  order; int /*<<< orphan*/  system_level; int /*<<< orphan*/  name; int /*<<< orphan*/  reference; struct acpi_device* device; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_6__ {int /*<<< orphan*/  bus_id; } ;
struct acpi_device {TYPE_3__ power; int /*<<< orphan*/  handle; struct acpi_power_resource* driver_data; TYPE_1__ pnp; } ;
struct TYPE_9__ {int member_0; union acpi_object* member_1; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OBJECT ;
typedef  TYPE_4__ ACPI_BUFFER ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_POWER_CLASS ; 
 int /*<<< orphan*/  ACPI_POWER_DEVICE_NAME ; 
#define  ACPI_POWER_RESOURCE_STATE_OFF 129 
#define  ACPI_POWER_RESOURCE_STATE_ON 128 
 int /*<<< orphan*/  ACPI_STATE_D0 ; 
 int /*<<< orphan*/  ACPI_STATE_D3 ; 
 int /*<<< orphan*/  ACPI_STATE_UNKNOWN ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct acpi_power_resource* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,char) ; 
 int /*<<< orphan*/  ExFreePool (struct acpi_power_resource*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  acpi_device_bid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int acpi_power_get_state (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  return_VALUE (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
acpi_power_add (
	struct acpi_device	*device)
{
	int	 result = 0, state;
	ACPI_STATUS		status = AE_OK;
	struct acpi_power_resource *resource = NULL;
	union acpi_object	acpi_object;
	ACPI_BUFFER	buffer = {sizeof(ACPI_OBJECT), &acpi_object};


	if (!device)
		return_VALUE(-1);

	resource = ExAllocatePoolWithTag(NonPagedPool,sizeof(struct acpi_power_resource),'IPCA');
	if (!resource)
		return_VALUE(-4);

	resource->device = device;
	//mutex_init(&resource->resource_lock);
	INIT_LIST_HEAD(&resource->reference);

	strcpy(resource->name, device->pnp.bus_id);
	strcpy(acpi_device_name(device), ACPI_POWER_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_POWER_CLASS);
	device->driver_data = resource;

	/* Evalute the object to get the system level and resource order. */
	status = AcpiEvaluateObject(device->handle, NULL, NULL, &buffer);
	if (ACPI_FAILURE(status)) {
		result = -15;
		goto end;
	}
	resource->system_level = acpi_object.PowerResource.SystemLevel;
	resource->order = acpi_object.PowerResource.ResourceOrder;

	result = acpi_power_get_state(device->handle, &state);
	if (result)
		goto end;

	switch (state) {
	case ACPI_POWER_RESOURCE_STATE_ON:
		device->power.state = ACPI_STATE_D0;
		break;
	case ACPI_POWER_RESOURCE_STATE_OFF:
		device->power.state = ACPI_STATE_D3;
		break;
	default:
		device->power.state = ACPI_STATE_UNKNOWN;
		break;
	}


	DPRINT("%s [%s] (%s)\n", acpi_device_name(device),
		acpi_device_bid(device), state?"on":"off");

end:
	if (result)
		ExFreePool(resource);

	return result;
}