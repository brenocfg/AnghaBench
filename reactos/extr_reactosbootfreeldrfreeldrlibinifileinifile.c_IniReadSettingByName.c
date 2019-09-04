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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  size_t ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  Flink; } ;
struct TYPE_7__ {TYPE_1__ SectionItemList; } ;
struct TYPE_6__ {TYPE_1__ ListEntry; int /*<<< orphan*/  ItemValue; int /*<<< orphan*/  ItemName; } ;
typedef  TYPE_2__* PINI_SECTION_ITEM ;
typedef  TYPE_3__* PINI_SECTION ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  char* PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_2__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INI_SECTION_ITEM ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 

BOOLEAN IniReadSettingByName(ULONG_PTR SectionId, PCSTR SettingName, PCHAR Buffer, ULONG BufferSize)
{
    PINI_SECTION        Section = (PINI_SECTION)SectionId;
    PINI_SECTION_ITEM    SectionItem;

    TRACE("IniReadSettingByName() SectionId = 0x%x\n", SectionId);

    // Loop through each section item and find the one they want
    SectionItem = CONTAINING_RECORD(Section->SectionItemList.Flink, INI_SECTION_ITEM, ListEntry);
    while (&SectionItem->ListEntry != &Section->SectionItemList)
    {
        // Check to see if this is the setting they want
        if (_stricmp(SettingName, SectionItem->ItemName) == 0)
        {
            TRACE("IniReadSettingByName() Setting \'%s\' found.\n", SettingName);
            TRACE("IniReadSettingByName() Setting value = %s\n", SectionItem->ItemValue);

            strncpy(Buffer, SectionItem->ItemValue, BufferSize - 1);
            Buffer[BufferSize - 1] = '\0';

            return TRUE;
        }

        // Get the next section item in the list
        SectionItem = CONTAINING_RECORD(SectionItem->ListEntry.Flink, INI_SECTION_ITEM, ListEntry);
    }

    WARN("IniReadSettingByName() Setting \'%s\' not found.\n", SettingName);

    return FALSE;
}