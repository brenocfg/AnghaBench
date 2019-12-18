#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG ;
struct TYPE_15__ {int DataSize; } ;
struct TYPE_14__ {int Affinity; scalar_t__ Vector; scalar_t__ Level; } ;
struct TYPE_12__ {int HighPart; scalar_t__ LowPart; } ;
struct TYPE_13__ {int Length; TYPE_1__ Start; } ;
struct TYPE_16__ {TYPE_4__ DeviceSpecificData; TYPE_3__ Interrupt; TYPE_2__ Port; } ;
struct TYPE_19__ {TYPE_5__ u; scalar_t__ Flags; void* ShareDisposition; int /*<<< orphan*/  Type; } ;
struct TYPE_18__ {int Version; int Revision; int Count; TYPE_8__* PartialDescriptors; } ;
struct TYPE_17__ {int BaudClock; } ;
typedef  int /*<<< orphan*/  PCONFIGURATION_COMPONENT_DATA ;
typedef  TYPE_6__* PCM_SERIAL_DEVICE_DATA ;
typedef  TYPE_7__* PCM_PARTIAL_RESOURCE_LIST ;
typedef  TYPE_8__* PCM_PARTIAL_RESOURCE_DESCRIPTOR ;
typedef  scalar_t__ (* GET_SERIAL_PORT ) (scalar_t__,scalar_t__*) ;
typedef  int /*<<< orphan*/  CM_SERIAL_DEVICE_DATA ;
typedef  int /*<<< orphan*/  CM_PARTIAL_RESOURCE_LIST ;
typedef  int /*<<< orphan*/  CM_PARTIAL_RESOURCE_DESCRIPTOR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ CM_RESOURCE_INTERRUPT_LATCHED ; 
 scalar_t__ CM_RESOURCE_PORT_IO ; 
 void* CmResourceShareDeviceExclusive ; 
 void* CmResourceShareUndetermined ; 
 int /*<<< orphan*/  CmResourceTypeDeviceSpecific ; 
 int /*<<< orphan*/  CmResourceTypeInterrupt ; 
 int /*<<< orphan*/  CmResourceTypePort ; 
 int ConsoleIn ; 
 int ConsoleOut ; 
 int /*<<< orphan*/  ControllerClass ; 
 int /*<<< orphan*/  CpDoesPortExist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DetectSerialPointerPeripheral (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FldrCreateComponentKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,int /*<<< orphan*/ *,TYPE_7__*,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_7__* FrLdrHeapAlloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int Input ; 
 int Output ; 
 int /*<<< orphan*/  Rs232PortInUse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SerialController ; 
 int /*<<< orphan*/  TAG_HW_RESOURCE_LIST ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  UlongToPtr (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 

VOID
DetectSerialPorts(PCONFIGURATION_COMPONENT_DATA BusKey, GET_SERIAL_PORT MachGetSerialPort, ULONG Count)
{
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptor;
    PCM_SERIAL_DEVICE_DATA SerialDeviceData;
    ULONG Irq;
    ULONG Base;
    CHAR Buffer[80];
    ULONG ControllerNumber = 0;
    PCONFIGURATION_COMPONENT_DATA ControllerKey;
    ULONG i;
    ULONG Size;

    TRACE("DetectSerialPorts()\n");

    for (i = 0; i < Count; i++)
    {
        Base = MachGetSerialPort(i, &Irq);
        if ((Base == 0) || !CpDoesPortExist(UlongToPtr(Base)))
            continue;

        TRACE("Found COM%u port at 0x%x\n", i + 1, Base);

        /* Set 'Identifier' value */
        sprintf(Buffer, "COM%ld", i + 1);

        /* Build full device descriptor */
        Size = sizeof(CM_PARTIAL_RESOURCE_LIST) +
               2 * sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR) +
               sizeof(CM_SERIAL_DEVICE_DATA);
        PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
        if (PartialResourceList == NULL)
        {
            ERR("Failed to allocate resource descriptor\n");
            continue;
        }
        memset(PartialResourceList, 0, Size);

        /* Initialize resource descriptor */
        PartialResourceList->Version = 1;
        PartialResourceList->Revision = 1;
        PartialResourceList->Count = 3;

        /* Set IO Port */
        PartialDescriptor = &PartialResourceList->PartialDescriptors[0];
        PartialDescriptor->Type = CmResourceTypePort;
        PartialDescriptor->ShareDisposition = CmResourceShareDeviceExclusive;
        PartialDescriptor->Flags = CM_RESOURCE_PORT_IO;
        PartialDescriptor->u.Port.Start.LowPart = Base;
        PartialDescriptor->u.Port.Start.HighPart = 0x0;
        PartialDescriptor->u.Port.Length = 7;

        /* Set Interrupt */
        PartialDescriptor = &PartialResourceList->PartialDescriptors[1];
        PartialDescriptor->Type = CmResourceTypeInterrupt;
        PartialDescriptor->ShareDisposition = CmResourceShareUndetermined;
        PartialDescriptor->Flags = CM_RESOURCE_INTERRUPT_LATCHED;
        PartialDescriptor->u.Interrupt.Level = Irq;
        PartialDescriptor->u.Interrupt.Vector = Irq;
        PartialDescriptor->u.Interrupt.Affinity = 0xFFFFFFFF;

        /* Set serial data (device specific) */
        PartialDescriptor = &PartialResourceList->PartialDescriptors[2];
        PartialDescriptor->Type = CmResourceTypeDeviceSpecific;
        PartialDescriptor->ShareDisposition = CmResourceShareUndetermined;
        PartialDescriptor->Flags = 0;
        PartialDescriptor->u.DeviceSpecificData.DataSize = sizeof(CM_SERIAL_DEVICE_DATA);

        SerialDeviceData =
            (PCM_SERIAL_DEVICE_DATA)&PartialResourceList->PartialDescriptors[3];
        SerialDeviceData->BaudClock = 1843200; /* UART Clock frequency (Hertz) */

        /* Create controller key */
        FldrCreateComponentKey(BusKey,
                               ControllerClass,
                               SerialController,
                               Output | Input | ConsoleIn | ConsoleOut,
                               ControllerNumber,
                               0xFFFFFFFF,
                               Buffer,
                               PartialResourceList,
                               Size,
                               &ControllerKey);

        if (!Rs232PortInUse(UlongToPtr(Base)))
        {
            /* Detect serial mouse */
            DetectSerialPointerPeripheral(ControllerKey, UlongToPtr(Base));
        }

        ControllerNumber++;
    }
}