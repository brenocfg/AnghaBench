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
typedef  int ULONG ;
struct TYPE_9__ {TYPE_3__* PciDevice; } ;
struct TYPE_6__ {int /*<<< orphan*/  AsULONG; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
struct TYPE_8__ {TYPE_2__ SlotNumber; int /*<<< orphan*/  BusNumber; } ;
typedef  int* PULONG ;
typedef  TYPE_4__* PPDO_DEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int HalGetBusDataByOffset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int HalSetBusDataByOffset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int MAXULONG ; 
 int /*<<< orphan*/  PCIConfiguration ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
PdoReadPciBar(PPDO_DEVICE_EXTENSION DeviceExtension,
              ULONG Offset,
              PULONG OriginalValue,
              PULONG NewValue)
{
    ULONG Size;
    ULONG AllOnes;

    /* Read the original value */
    Size = HalGetBusDataByOffset(PCIConfiguration,
                                 DeviceExtension->PciDevice->BusNumber,
                                 DeviceExtension->PciDevice->SlotNumber.u.AsULONG,
                                 OriginalValue,
                                 Offset,
                                 sizeof(ULONG));
    if (Size != sizeof(ULONG))
    {
        DPRINT1("Wrong size %lu\n", Size);
        return FALSE;
    }

    /* Write all ones to determine which bits are held to zero */
    AllOnes = MAXULONG;
    Size = HalSetBusDataByOffset(PCIConfiguration,
                                 DeviceExtension->PciDevice->BusNumber,
                                 DeviceExtension->PciDevice->SlotNumber.u.AsULONG,
                                 &AllOnes,
                                 Offset,
                                 sizeof(ULONG));
    if (Size != sizeof(ULONG))
    {
        DPRINT1("Wrong size %lu\n", Size);
        return FALSE;
    }

    /* Get the range length */
    Size = HalGetBusDataByOffset(PCIConfiguration,
                                 DeviceExtension->PciDevice->BusNumber,
                                 DeviceExtension->PciDevice->SlotNumber.u.AsULONG,
                                 NewValue,
                                 Offset,
                                 sizeof(ULONG));
    if (Size != sizeof(ULONG))
    {
        DPRINT1("Wrong size %lu\n", Size);
        return FALSE;
    }

    /* Restore original value */
    Size = HalSetBusDataByOffset(PCIConfiguration,
                                 DeviceExtension->PciDevice->BusNumber,
                                 DeviceExtension->PciDevice->SlotNumber.u.AsULONG,
                                 OriginalValue,
                                 Offset,
                                 sizeof(ULONG));
    if (Size != sizeof(ULONG))
    {
        DPRINT1("Wrong size %lu\n", Size);
        return FALSE;
    }

    return TRUE;
}