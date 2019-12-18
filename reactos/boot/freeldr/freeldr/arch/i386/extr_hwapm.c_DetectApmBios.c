#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
struct TYPE_5__ {scalar_t__ Count; scalar_t__ Revision; scalar_t__ Version; } ;
typedef  int /*<<< orphan*/  PCONFIGURATION_COMPONENT_DATA ;
typedef  TYPE_1__* PCM_PARTIAL_RESOURCE_LIST ;
typedef  int /*<<< orphan*/  CM_PARTIAL_RESOURCE_LIST ;
typedef  int /*<<< orphan*/  CM_PARTIAL_RESOURCE_DESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  AdapterClass ; 
 scalar_t__ FindApmBios () ; 
 int /*<<< orphan*/  FldrCreateComponentKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,char*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* FrLdrHeapAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiFunctionAdapter ; 
 int /*<<< orphan*/  TAG_HW_RESOURCE_LIST ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

VOID
DetectApmBios(PCONFIGURATION_COMPONENT_DATA SystemKey, ULONG *BusNumber)
{
    PCONFIGURATION_COMPONENT_DATA BiosKey;
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    ULONG Size;

    Size = sizeof(CM_PARTIAL_RESOURCE_LIST) -
           sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR);

    if (FindApmBios())
    {
        /* Create 'Configuration Data' value */
        PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
        memset(PartialResourceList, 0, Size);
        PartialResourceList->Version = 0;
        PartialResourceList->Revision = 0;
        PartialResourceList->Count = 0;

        /* Create new bus key */
        FldrCreateComponentKey(SystemKey,
                               AdapterClass,
                               MultiFunctionAdapter,
                               0x0,
                               0x0,
                               0xFFFFFFFF,
                               "APM",
                               PartialResourceList,
                               Size,
                               &BiosKey);

        /* Increment bus number */
        (*BusNumber)++;
    }

    /* FIXME: Add configuration data */
}