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
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/ * PUCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_ConOutPrintf (char*,...) ; 

void HexDump(PUCHAR buffer, ULONG size)
{
    ULONG offset = 0;
    PUCHAR ptr;

    while (offset < (size & ~15))
    {
        ptr = (PUCHAR)((ULONG_PTR)buffer + offset);
        CONSOLE_ConOutPrintf("%04lx  %02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx %02hx\n",
               offset,
               ptr[0],
               ptr[1],
               ptr[2],
               ptr[3],
               ptr[4],
               ptr[5],
               ptr[6],
               ptr[7],
               ptr[8],
               ptr[9],
               ptr[10],
               ptr[11],
               ptr[12],
               ptr[13],
               ptr[14],
               ptr[15]);
        offset += 16;
    }

    if (offset < size)
    {
        ptr = (PUCHAR)((ULONG_PTR)buffer + offset);
        CONSOLE_ConOutPrintf("%04lx ", offset);
        while (offset < size)
        {
            CONSOLE_ConOutPrintf(" %02hx", *ptr);
            offset++;
            ptr++;
        }

        CONSOLE_ConOutPrintf("\n");
    }

    CONSOLE_ConOutPrintf("\n");
}