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
typedef  scalar_t__ ULONG ;
typedef  char* PCHAR ;

/* Variables and functions */

ULONG IniGetNextLine(PCHAR IniFileData, ULONG IniFileSize, PCHAR Buffer, ULONG BufferSize, ULONG CurrentOffset)
{
    ULONG        Idx;

    // Loop through grabbing chars until we hit the end of the
    // file or we encounter a new line char
    for (Idx=0; (CurrentOffset < IniFileSize); CurrentOffset++)
    {
        // If we haven't exceeded our buffer size yet
        // then store another char
        if (Idx < (BufferSize - 1))
        {
            Buffer[Idx++] = IniFileData[CurrentOffset];
        }

        // Check for new line char
        if (IniFileData[CurrentOffset] == '\n')
        {
            CurrentOffset++;
            break;
        }
    }

    // Terminate the string
    Buffer[Idx] = '\0';

    // Get rid of newline & linefeed characters (if any)
    while(Idx && (Buffer[--Idx] == '\n' || Buffer[Idx] == '\r'))
        Buffer[Idx] = '\0';

    // Send back new offset
    return CurrentOffset;
}