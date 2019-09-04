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
typedef  int* PCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL TrimNonPrintable(PCHAR DmiString)
{
    PCHAR c = DmiString;
    if (!c)
    {
        return FALSE;
    }
    while (*c)
    {
        if (*c >= 0x20 && *c <= 0x7e)
        {
            c++;
        }
        else
        {
            *c = 0;
            return TRUE;
        }
    }
    return FALSE;
}