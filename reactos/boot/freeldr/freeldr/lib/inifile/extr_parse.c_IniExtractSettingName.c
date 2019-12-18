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

VOID IniExtractSettingName(PCHAR SettingName, PCHAR SettingNameLine, ULONG LineLength)
{
    ULONG        Idx;
    ULONG        DestIdx;

    // Skip whitespace
    for (Idx=0; Idx<LineLength; Idx++)
    {
        if ((SettingNameLine[Idx] == ' ') ||
            (SettingNameLine[Idx] == '\t'))
        {
            continue;
        }
        else
        {
            break;
        }
    }

    // Get the characters up until the '=' equals sign or EOL
    for (DestIdx=0; Idx<LineLength; Idx++)
    {
        if ((SettingNameLine[Idx] == '=') ||
            (SettingNameLine[Idx] == '\0'))
        {
            break;
        }

        // Grab a character and increment DestIdx
        SettingName[DestIdx] = SettingNameLine[Idx];
        DestIdx++;
    }

    // Terminate the string
    SettingName[DestIdx] = '\0';
}