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

ULONG IniGetNextLineSize(PCHAR IniFileData, ULONG IniFileSize, ULONG CurrentOffset)
{
    ULONG        LineCharCount = 0;

    // Loop through counting chars until we hit the end of the
    // file or we encounter a new line char
    for (; (CurrentOffset < IniFileSize); CurrentOffset++)
    {
        // Increment the line character count
        LineCharCount++;

        // Check for new line char
        if (IniFileData[CurrentOffset] == '\n')
        {
            break;
        }
    }

    // Add one for the NULL-terminator
    LineCharCount++;

    // Send back line character count
    return LineCharCount;
}