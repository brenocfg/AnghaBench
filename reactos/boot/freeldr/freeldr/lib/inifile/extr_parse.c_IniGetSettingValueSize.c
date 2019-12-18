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

ULONG IniGetSettingValueSize(PCHAR SettingValueLine, ULONG LineLength)
{
    ULONG        Idx;
    ULONG        ValueSize;

    // Skip whitespace
    for (Idx=0; Idx<LineLength; Idx++)
    {
        if ((SettingValueLine[Idx] == ' ') ||
            (SettingValueLine[Idx] == '\t'))
        {
            continue;
        }
        else
        {
            break;
        }
    }

    // Skip the characters up until the '=' equals sign or EOL
    for (; Idx<LineLength; Idx++)
    {
        if (SettingValueLine[Idx] == '=')
        {
            Idx++;
            break;
        }

        // If we hit EOL then obviously the value size is zero
        if (SettingValueLine[Idx] == '\0')
        {
            return 0;
        }
    }

    // Count the characters up until the EOL
    for (ValueSize=0; Idx<LineLength; Idx++)
    {
        if (SettingValueLine[Idx] == '\0')
        {
            break;
        }

        // Increment the count
        ValueSize++;
    }

    // Add one for the NULL-terminator
    ValueSize++;

    return ValueSize;
}