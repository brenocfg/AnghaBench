#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  Flink; } ;
struct TYPE_8__ {TYPE_1__ SectionItemList; } ;
struct TYPE_7__ {TYPE_1__ ListEntry; } ;
typedef  TYPE_2__* PINI_SECTION_ITEM ;
typedef  TYPE_3__* PINI_SECTION ;

/* Variables and functions */
 TYPE_2__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INI_SECTION_ITEM ; 
 int /*<<< orphan*/  ListEntry ; 

PINI_SECTION_ITEM IniGetSettingByNumber(ULONG_PTR SectionId, ULONG SettingNumber)
{
    PINI_SECTION        Section = (PINI_SECTION)SectionId;
    PINI_SECTION_ITEM    SectionItem;

    // Loop through each section item and find the one they want
    SectionItem = CONTAINING_RECORD(Section->SectionItemList.Flink, INI_SECTION_ITEM, ListEntry);
    while (&SectionItem->ListEntry != &Section->SectionItemList)
    {
        // Check to see if this is the setting they want
        if (SettingNumber == 0)
        {
            return SectionItem;
        }

        // Nope, keep going
        SettingNumber--;

        // Get the next section item in the list
        SectionItem = CONTAINING_RECORD(SectionItem->ListEntry.Flink, INI_SECTION_ITEM, ListEntry);
    }
    return NULL;
}