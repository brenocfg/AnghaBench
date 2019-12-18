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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int* PUCHAR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _wcsnicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** pszDaysOfWeekArray ; 
 int /*<<< orphan*/ * wcschr (int /*<<< orphan*/ *,int) ; 
 int wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
BOOL
ParseDaysOfWeek(
    PWSTR pszBuffer,
    PUCHAR pucDaysOfWeek)
{
    PWSTR startPtr, endPtr;
    INT nLength, i;

    if (wcslen(pszBuffer) == 0)
        return FALSE;

    startPtr = pszBuffer;
    endPtr = NULL;
    for (;;)
    {
        endPtr = wcschr(startPtr, L',');
        if (endPtr == NULL)
            nLength = wcslen(startPtr);
        else
            nLength = (INT)((ULONG_PTR)endPtr - (ULONG_PTR)startPtr) / sizeof(WCHAR);

        for (i = 0; i < 7; i++)
        {
            if (nLength == wcslen(pszDaysOfWeekArray[i]) &&
                _wcsnicmp(startPtr, pszDaysOfWeekArray[i], nLength) == 0)
            {
                *pucDaysOfWeek |= (1 << i);
                break;
            }
        }

        if (endPtr == NULL)
            return TRUE;

        startPtr = endPtr + 1;
        endPtr = NULL;
    }

    return FALSE;
}