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
typedef  int* PINT ;
typedef  int* LPWSTR ;

/* Variables and functions */
 scalar_t__ GetULONG (int*) ; 

__attribute__((used)) static ULONG
GetULONG2(LPWSTR String1, LPWSTR String2, PINT i)
{
    ULONG Value;

    /* Check the first string value */
    Value = GetULONG(String1);
    if (Value == (ULONG)-1)
    {
        /* Check the second string value isn't a switch */
        if (String2[0] != L'-')
        {
            /* Check the value */
            Value = GetULONG(String2);
            *i += 1;
        }
    }

    return Value;
}