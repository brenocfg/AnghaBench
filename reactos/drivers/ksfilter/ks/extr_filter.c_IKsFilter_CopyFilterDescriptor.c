#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  Bag; TYPE_10__* Descriptor; } ;
struct TYPE_15__ {TYPE_1__ Filter; } ;
struct TYPE_14__ {int PropertyItemSize; int PropertySetsCount; int /*<<< orphan*/  PropertySets; } ;
struct TYPE_13__ {scalar_t__ AutomationTable; } ;
struct TYPE_11__ {int /*<<< orphan*/  AutomationTable; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PKSAUTOMATION_TABLE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KSPROPERTY_ITEM ;
typedef  TYPE_2__ KSFILTER_DESCRIPTOR ;
typedef  TYPE_3__ KSAUTOMATION_TABLE ;
typedef  TYPE_4__ IKsFilterImpl ;

/* Variables and functions */
 TYPE_10__* AllocateItem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FilterPropertySet ; 
 int /*<<< orphan*/  FreeItem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KsAddItemToObjectBag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KsMergeAutomationTables (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlMoveMemory (int /*<<< orphan*/ ,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 

NTSTATUS
IKsFilter_CopyFilterDescriptor(
    IKsFilterImpl * This,
    const KSFILTER_DESCRIPTOR* FilterDescriptor)
{
    NTSTATUS Status;
    KSAUTOMATION_TABLE AutomationTable;

    This->Filter.Descriptor = AllocateItem(NonPagedPool, sizeof(KSFILTER_DESCRIPTOR));
    if (!This->Filter.Descriptor)
        return STATUS_INSUFFICIENT_RESOURCES;

    Status = KsAddItemToObjectBag(This->Filter.Bag, (PVOID)This->Filter.Descriptor, NULL);
    if (!NT_SUCCESS(Status))
    {
        FreeItem((PVOID)This->Filter.Descriptor);
        This->Filter.Descriptor = NULL;
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* copy filter descriptor fields */
    RtlMoveMemory((PVOID)This->Filter.Descriptor, FilterDescriptor, sizeof(KSFILTER_DESCRIPTOR));

    /* zero automation table */
    RtlZeroMemory(&AutomationTable, sizeof(KSAUTOMATION_TABLE));

    /* setup filter property sets */
    AutomationTable.PropertyItemSize = sizeof(KSPROPERTY_ITEM);
    AutomationTable.PropertySetsCount = 3;
    AutomationTable.PropertySets = FilterPropertySet;

    /* merge filter automation table */
    Status = KsMergeAutomationTables((PKSAUTOMATION_TABLE*)&This->Filter.Descriptor->AutomationTable, (PKSAUTOMATION_TABLE)FilterDescriptor->AutomationTable, &AutomationTable, This->Filter.Bag);

    return Status;
}