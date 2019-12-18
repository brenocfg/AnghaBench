#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_4__ {int /*<<< orphan*/  ListEntry; int /*<<< orphan*/  SectionItemList; void* SectionName; } ;
typedef  TYPE_1__* PINI_SECTION ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  int /*<<< orphan*/  INI_SECTION ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IniFileSectionCount ; 
 int /*<<< orphan*/  IniFileSectionListHead ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TAG_INI_NAME ; 
 int /*<<< orphan*/  TAG_INI_SECTION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcpy (void*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

BOOLEAN IniAddSection(PCSTR SectionName, ULONG_PTR* SectionId)
{
    PINI_SECTION    Section;

    // Allocate a new section structure
    Section = FrLdrTempAlloc(sizeof(INI_SECTION), TAG_INI_SECTION);
    if (!Section)
    {
        return FALSE;
    }

    RtlZeroMemory(Section, sizeof(INI_SECTION));

    // Allocate the section name buffer
    Section->SectionName = FrLdrTempAlloc(strlen(SectionName) + sizeof(CHAR), TAG_INI_NAME);
    if (!Section->SectionName)
    {
        FrLdrTempFree(Section, TAG_INI_SECTION);
        return FALSE;
    }

    // Get the section name
    strcpy(Section->SectionName, SectionName);
    InitializeListHead(&Section->SectionItemList);

    // Add it to the section list head
    IniFileSectionCount++;
    InsertHeadList(&IniFileSectionListHead, &Section->ListEntry);

    *SectionId = (ULONG_PTR)Section;

    return TRUE;
}