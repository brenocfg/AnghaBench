#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
typedef  char* PCHAR ;

/* Variables and functions */

VOID IniExtractSectionName(PCHAR SectionName, PCHAR SectionNameLine, ULONG LineLength)
{
    ULONG        Idx;
    ULONG        DestIdx;

    // Find the opening bracket (skipping whitespace)
    for (Idx=0; Idx<LineLength; Idx++)
    {
        if ((SectionNameLine[Idx] == ' ') ||
            (SectionNameLine[Idx] == '\t'))
        {
            continue;
        }
        else //if (SectionNameLine[Idx] == '[')
        {
            break;
        }
    }

    // Skip past the opening bracket
    Idx++;

    // Count the characters up until the closing bracket or EOL
    for (DestIdx=0; Idx<LineLength; Idx++)
    {
        if ((SectionNameLine[Idx] == ']') ||
            (SectionNameLine[Idx] == '\0'))
        {
            break;
        }

        // Grab a character and increment DestIdx
        SectionName[DestIdx] = SectionNameLine[Idx];
        DestIdx++;
    }

    // Terminate the string
    SectionName[DestIdx] = '\0';
}