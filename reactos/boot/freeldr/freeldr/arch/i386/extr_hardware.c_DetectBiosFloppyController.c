#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_14__ {int Channel; scalar_t__ Port; } ;
struct TYPE_13__ {int Level; int Vector; int Affinity; } ;
struct TYPE_11__ {int LowPart; int HighPart; } ;
struct TYPE_12__ {int Length; TYPE_1__ Start; } ;
struct TYPE_15__ {TYPE_4__ Dma; TYPE_3__ Interrupt; TYPE_2__ Port; } ;
struct TYPE_17__ {TYPE_5__ u; scalar_t__ Flags; void* ShareDisposition; int /*<<< orphan*/  Type; } ;
struct TYPE_16__ {int Version; int Revision; int Count; TYPE_7__* PartialDescriptors; } ;
typedef  int /*<<< orphan*/ * PCONFIGURATION_COMPONENT_DATA ;
typedef  TYPE_6__* PCM_PARTIAL_RESOURCE_LIST ;
typedef  TYPE_7__* PCM_PARTIAL_RESOURCE_DESCRIPTOR ;
typedef  int /*<<< orphan*/  CM_PARTIAL_RESOURCE_LIST ;
typedef  int /*<<< orphan*/  CM_PARTIAL_RESOURCE_DESCRIPTOR ;

/* Variables and functions */
 scalar_t__ CM_RESOURCE_INTERRUPT_LATCHED ; 
 scalar_t__ CM_RESOURCE_PORT_IO ; 
 void* CmResourceShareDeviceExclusive ; 
 void* CmResourceShareUndetermined ; 
 int /*<<< orphan*/  CmResourceTypeDma ; 
 int /*<<< orphan*/  CmResourceTypeInterrupt ; 
 int /*<<< orphan*/  CmResourceTypePort ; 
 int /*<<< orphan*/  ControllerClass ; 
 int /*<<< orphan*/  DetectBiosFloppyPeripheral (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DiskController ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FldrCreateComponentKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,TYPE_6__*,int,int /*<<< orphan*/ **) ; 
 TYPE_6__* FrLdrHeapAlloc (int,int /*<<< orphan*/ ) ; 
 int Input ; 
 int MachGetFloppyCount () ; 
 int Output ; 
 int /*<<< orphan*/  TAG_HW_RESOURCE_LIST ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
PCONFIGURATION_COMPONENT_DATA
DetectBiosFloppyController(PCONFIGURATION_COMPONENT_DATA BusKey)
{
    PCONFIGURATION_COMPONENT_DATA ControllerKey;
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptor;
    ULONG Size;
    ULONG FloppyCount;

    FloppyCount = MachGetFloppyCount();
    TRACE("Floppy count: %u\n", FloppyCount);

    /* Always create a BIOS disk controller, no matter if we have floppy drives or not */
    Size = sizeof(CM_PARTIAL_RESOURCE_LIST) +
           2 * sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR);
    PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
    if (PartialResourceList == NULL)
    {
        ERR("Failed to allocate resource descriptor\n");
        return NULL;
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
    PartialDescriptor->u.Port.Start.LowPart = 0x03F0;
    PartialDescriptor->u.Port.Start.HighPart = 0x0;
    PartialDescriptor->u.Port.Length = 8;

    /* Set Interrupt */
    PartialDescriptor = &PartialResourceList->PartialDescriptors[1];
    PartialDescriptor->Type = CmResourceTypeInterrupt;
    PartialDescriptor->ShareDisposition = CmResourceShareUndetermined;
    PartialDescriptor->Flags = CM_RESOURCE_INTERRUPT_LATCHED;
    PartialDescriptor->u.Interrupt.Level = 6;
    PartialDescriptor->u.Interrupt.Vector = 6;
    PartialDescriptor->u.Interrupt.Affinity = 0xFFFFFFFF;

    /* Set DMA channel */
    PartialDescriptor = &PartialResourceList->PartialDescriptors[2];
    PartialDescriptor->Type = CmResourceTypeDma;
    PartialDescriptor->ShareDisposition = CmResourceShareUndetermined;
    PartialDescriptor->Flags = 0;
    PartialDescriptor->u.Dma.Channel = 2;
    PartialDescriptor->u.Dma.Port = 0;

    /* Create floppy disk controller */
    FldrCreateComponentKey(BusKey,
                           ControllerClass,
                           DiskController,
                           Output | Input,
                           0x0,
                           0xFFFFFFFF,
                           NULL,
                           PartialResourceList,
                           Size,
                           &ControllerKey);
    TRACE("Created key: DiskController\\0\n");

    if (FloppyCount)
        DetectBiosFloppyPeripheral(ControllerKey);

    return ControllerKey;
}