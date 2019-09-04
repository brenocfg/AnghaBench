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
typedef  scalar_t__ PWSTR ;
typedef  int* PINT ;
typedef  scalar_t__ PCWSTR ;

/* Variables and functions */
 int wcstol (scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static PCWSTR
FindPortNum(PCWSTR argStr, PINT PortNum)
{
    PWSTR endptr = NULL;

    *PortNum = wcstol(argStr, &endptr, 10);
    if (endptr == argStr)
    {
        *PortNum = -1;
        return NULL;
    }

    return endptr;
}