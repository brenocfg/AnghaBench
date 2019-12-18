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
struct TYPE_2__ {scalar_t__ present; } ;
struct acpi_device {TYPE_1__ status; struct acpi_device* parent; scalar_t__ handle; } ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int ACPI_OBJECT_TYPE ;
typedef  scalar_t__ ACPI_HANDLE ;

/* Variables and functions */
 int ACPI_BUS_TYPE_DEVICE ; 
 int ACPI_BUS_TYPE_POWER ; 
 int ACPI_BUS_TYPE_PROCESSOR ; 
 int ACPI_BUS_TYPE_THERMAL ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
#define  ACPI_TYPE_DEVICE 131 
 int ACPI_TYPE_LOCAL_SCOPE ; 
#define  ACPI_TYPE_POWER 130 
#define  ACPI_TYPE_PROCESSOR 129 
#define  ACPI_TYPE_THERMAL 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiGetNextObject (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  AcpiGetParent (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  AcpiGetType (scalar_t__,int*) ; 
 int /*<<< orphan*/  acpi_bus_add (struct acpi_device**,struct acpi_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  return_VALUE (int /*<<< orphan*/ ) ; 

int
acpi_bus_scan (
	struct acpi_device	*start)
{
	ACPI_STATUS		status = AE_OK;
	struct acpi_device	*parent = NULL;
	struct acpi_device	*child = NULL;
	ACPI_HANDLE		phandle = 0;
	ACPI_HANDLE		chandle = 0;
	ACPI_OBJECT_TYPE	type = 0;
	UINT32			level = 1;

	if (!start)
		return_VALUE(AE_BAD_PARAMETER);

	parent = start;
	phandle = start->handle;

	/*
	 * Parse through the ACPI namespace, identify all 'devices', and
	 * create a new 'struct acpi_device' for each.
	 */
	while ((level > 0) && parent) {

		status = AcpiGetNextObject(ACPI_TYPE_ANY, phandle,
			chandle, &chandle);

		/*
		 * If this scope is exhausted then move our way back up.
		 */
		if (ACPI_FAILURE(status)) {
			level--;
			chandle = phandle;
			AcpiGetParent(phandle, &phandle);
			if (parent->parent)
				parent = parent->parent;
			continue;
		}

		status = AcpiGetType(chandle, &type);
		if (ACPI_FAILURE(status))
			continue;

		/*
		 * If this is a scope object then parse it (depth-first).
		 */
		if (type == ACPI_TYPE_LOCAL_SCOPE) {
			level++;
			phandle = chandle;
			chandle = 0;
			continue;
		}

		/*
		 * We're only interested in objects that we consider 'devices'.
		 */
		switch (type) {
		case ACPI_TYPE_DEVICE:
			type = ACPI_BUS_TYPE_DEVICE;
			break;
		case ACPI_TYPE_PROCESSOR:
			type = ACPI_BUS_TYPE_PROCESSOR;
			break;
		case ACPI_TYPE_THERMAL:
			type = ACPI_BUS_TYPE_THERMAL;
			break;
		case ACPI_TYPE_POWER:
			type = ACPI_BUS_TYPE_POWER;
			break;
		default:
			continue;
		}

		status = acpi_bus_add(&child, parent, chandle, type);
		if (ACPI_FAILURE(status))
			continue;

		/*
		 * If the device is present, enabled, and functioning then
		 * parse its scope (depth-first).  Note that we need to
		 * represent absent devices to facilitate PnP notifications
		 * -- but only the subtree head (not all of its children,
		 * which will be enumerated when the parent is inserted).
		 *
		 * TBD: Need notifications and other detection mechanisms
		 *	in place before we can fully implement this.
		 */
		if (child->status.present) {
			status = AcpiGetNextObject(ACPI_TYPE_ANY, chandle,
				0, NULL);
			if (ACPI_SUCCESS(status)) {
				level++;
				phandle = chandle;
				chandle = 0;
				parent = child;
			}
		}
	}

	return_VALUE(0);
}