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
typedef  int* PWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  iswalpha (int) ; 
 int wcslen (int*) ; 

__attribute__((used)) static
BOOL
ValidateDeviceName(PWSTR DevName)
{
    DWORD Len;

    Len = wcslen(DevName);
    if (Len != 2)
    {
        return FALSE;
    }

    if (!iswalpha(DevName[0]) || DevName[1] != L':')
    {
        return FALSE;
    }

    return TRUE;
}