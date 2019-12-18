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
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int* PDWORD ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOL
ParseDay(
    PWSTR pszString,
    PWSTR *ShortDays,
    PWSTR *LongDays,
    PDWORD pdwDay)
{
    DWORD i;

    for (i = 0; i < 7; i++)
    {
        if (_wcsicmp(pszString, ShortDays[i]) == 0 ||
            _wcsicmp(pszString, LongDays[i]) == 0)
        {
            *pdwDay = i;
            return TRUE;
        }
    }

    return FALSE;
}