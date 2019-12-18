#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_5__ {int /*<<< orphan*/  Flink; } ;
struct TYPE_4__ {TYPE_2__ ListEntry; int /*<<< orphan*/  SectionName; } ;
typedef  TYPE_1__* PINI_SECTION ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INI_SECTION ; 
 TYPE_2__ IniFileSectionListHead ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN IniOpenSection(PCSTR SectionName, ULONG_PTR* SectionId)
{
    PINI_SECTION    Section;

    TRACE("IniOpenSection() SectionName = %s\n", SectionName);

    // Loop through each section and find the one they want
    Section = CONTAINING_RECORD(IniFileSectionListHead.Flink, INI_SECTION, ListEntry);
    while (&Section->ListEntry != &IniFileSectionListHead)
    {
        // Compare against the section name
        if (_stricmp(SectionName, Section->SectionName) == 0)
        {
            // We found it
            if (SectionId)
                *SectionId = (ULONG_PTR)Section;
            TRACE("IniOpenSection() Found it! SectionId = 0x%x\n", SectionId);
            return TRUE;
        }

        // Get the next section in the list
        Section = CONTAINING_RECORD(Section->ListEntry.Flink, INI_SECTION, ListEntry);
    }

    TRACE("IniOpenSection() Section not found.\n");

    return FALSE;
}