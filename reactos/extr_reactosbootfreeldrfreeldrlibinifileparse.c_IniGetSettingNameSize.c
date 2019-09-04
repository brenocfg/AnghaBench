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
typedef  size_t ULONG ;
typedef  char* PCHAR ;

/* Variables and functions */

ULONG IniGetSettingNameSize(PCHAR SettingNameLine, ULONG LineLength)
{
    ULONG        Idx;
    ULONG        NameSize;

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

    // Count the characters up until the '=' equals sign or EOL
    for (NameSize=0; Idx<LineLength; Idx++)
    {
        if ((SettingNameLine[Idx] == '=') ||
            (SettingNameLine[Idx] == '\0'))
        {
            break;
        }

        // Increment the count
        NameSize++;
    }

    // Add one for the NULL-terminator
    NameSize++;

    return NameSize;
}