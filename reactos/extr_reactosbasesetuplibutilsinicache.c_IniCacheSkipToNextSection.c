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
typedef  char* PCHAR ;

/* Variables and functions */

__attribute__((used)) static
PCHAR
IniCacheSkipToNextSection(
    PCHAR Ptr)
{
    while (*Ptr != 0 && *Ptr != '[')
    {
        while (*Ptr != 0 && *Ptr != L'\n')
        {
            Ptr++;
        }

        Ptr++;
    }

    return (*Ptr == 0) ? NULL : Ptr;
}