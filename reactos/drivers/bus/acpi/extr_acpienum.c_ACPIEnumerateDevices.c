#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  next; } ;
struct TYPE_6__ {int /*<<< orphan*/  next; } ;
struct TYPE_5__ {scalar_t__ hardware_id; } ;
struct TYPE_8__ {scalar_t__ enabled; scalar_t__ present; } ;
struct acpi_device {TYPE_3__ node; struct acpi_device* parent; TYPE_2__ children; TYPE_1__ flags; TYPE_4__ status; } ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  PFDO_DEVICE_DATA ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  Bus_PlugInDevice (struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 scalar_t__ HAS_CHILDREN (struct acpi_device*) ; 
 scalar_t__ HAS_SIBLINGS (struct acpi_device*) ; 
 struct acpi_device* NODE_TO_DEVICE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 struct acpi_device* acpi_root ; 

NTSTATUS
ACPIEnumerateDevices(PFDO_DEVICE_DATA DeviceExtension)
{
    ULONG Count = 0;
    struct acpi_device *Device = acpi_root;

    while(Device)
    {
        if (Device->status.present && Device->status.enabled &&
            Device->flags.hardware_id)
        {
            Bus_PlugInDevice(Device, DeviceExtension);
            Count++;
        }

        if (HAS_CHILDREN(Device)) {
            Device = NODE_TO_DEVICE(Device->children.next);
            continue;
        }
        if (HAS_SIBLINGS(Device)) {
            Device = NODE_TO_DEVICE(Device->node.next);
            continue;
        }
        while ((Device = Device->parent)) {
            if (HAS_SIBLINGS(Device)) {
                Device = NODE_TO_DEVICE(Device->node.next);
                break;
            }
        }
    }
    DPRINT("acpi device count: %d\n", Count);
    return STATUS_SUCCESS;
}