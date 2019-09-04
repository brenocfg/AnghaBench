#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_7__ {int /*<<< orphan*/  SectionItemList; int /*<<< orphan*/  SectionItemCount; } ;
struct TYPE_6__ {int /*<<< orphan*/  ListEntry; struct TYPE_6__* ItemValue; struct TYPE_6__* ItemName; } ;
typedef  TYPE_1__* PINI_SECTION_ITEM ;
typedef  TYPE_2__* PINI_SECTION ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  int /*<<< orphan*/  INI_SECTION_ITEM ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TAG_INI_NAME ; 
 int /*<<< orphan*/  TAG_INI_SECTION_ITEM ; 
 int /*<<< orphan*/  TAG_INI_VALUE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcpy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

BOOLEAN IniAddSettingValueToSection(ULONG_PTR SectionId, PCSTR SettingName, PCSTR SettingValue)
{
    PINI_SECTION        Section = (PINI_SECTION)SectionId;
    PINI_SECTION_ITEM    SectionItem;

    // Allocate a new item structure
    SectionItem = FrLdrTempAlloc(sizeof(INI_SECTION_ITEM), TAG_INI_SECTION_ITEM);
    if (!SectionItem)
    {
        return FALSE;
    }

    RtlZeroMemory(SectionItem, sizeof(INI_SECTION_ITEM));

    // Allocate the setting name buffer
    SectionItem->ItemName = FrLdrTempAlloc(strlen(SettingName) + 1, TAG_INI_NAME);
    if (!SectionItem->ItemName)
    {
        FrLdrTempFree(SectionItem, TAG_INI_SECTION_ITEM);
        return FALSE;
    }

    // Allocate the setting value buffer
    SectionItem->ItemValue = FrLdrTempAlloc(strlen(SettingValue) + 1, TAG_INI_VALUE);
    if (!SectionItem->ItemValue)
    {
        FrLdrTempFree(SectionItem->ItemName, TAG_INI_NAME);
        FrLdrTempFree(SectionItem, TAG_INI_SECTION_ITEM);
        return FALSE;
    }

    strcpy(SectionItem->ItemName, SettingName);
    strcpy(SectionItem->ItemValue, SettingValue);

    // Add it to the current section
    Section->SectionItemCount++;
    InsertTailList(&Section->SectionItemList, &SectionItem->ListEntry);

    return TRUE;
}