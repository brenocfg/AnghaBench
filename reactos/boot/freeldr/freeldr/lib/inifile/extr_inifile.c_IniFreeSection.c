#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {struct TYPE_6__* SectionName; struct TYPE_6__* ItemValue; struct TYPE_6__* ItemName; int /*<<< orphan*/  SectionItemList; } ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  TYPE_1__* PINI_SECTION_ITEM ;
typedef  TYPE_1__* PINI_SECTION ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INI_SECTION_ITEM ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoveHeadList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAG_INI_NAME ; 
 int /*<<< orphan*/  TAG_INI_SECTION ; 
 int /*<<< orphan*/  TAG_INI_SECTION_ITEM ; 
 int /*<<< orphan*/  TAG_INI_VALUE ; 

VOID IniFreeSection(PINI_SECTION Section)
{
    PLIST_ENTRY ListEntry;
    PINI_SECTION_ITEM SectionItem;

    // Loop while there are section items
    while (!IsListEmpty(&Section->SectionItemList))
    {
        // Remove the section item
        ListEntry = RemoveHeadList(&Section->SectionItemList);
        SectionItem = CONTAINING_RECORD(ListEntry, INI_SECTION_ITEM, ListEntry);

        // Free it
        FrLdrTempFree(SectionItem->ItemName, TAG_INI_NAME);
        FrLdrTempFree(SectionItem->ItemValue, TAG_INI_VALUE);
        FrLdrTempFree(SectionItem, TAG_INI_SECTION_ITEM);
    }

    FrLdrTempFree(Section->SectionName, TAG_INI_NAME);
    FrLdrTempFree(Section, TAG_INI_SECTION);
}