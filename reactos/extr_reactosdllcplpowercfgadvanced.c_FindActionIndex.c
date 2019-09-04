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
typedef  scalar_t__ POWER_ACTION ;
typedef  size_t INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */

__attribute__((used)) static INT
FindActionIndex(POWER_ACTION * lpAction, DWORD dwActionSize, POWER_ACTION poAction)
{
    INT Index;

    for (Index = 0; Index < (INT)dwActionSize; Index++)
    {
        if (lpAction[Index] == poAction)
            return Index;
    }

    return -1;
}