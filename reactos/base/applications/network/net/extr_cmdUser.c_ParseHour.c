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
typedef  scalar_t__* PWSTR ;
typedef  scalar_t__* PWCHAR ;
typedef  int* PLONG ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UNICODE_NULL ; 
 scalar_t__ _wcsicmp (scalar_t__*,scalar_t__*) ; 
 scalar_t__ iswdigit (scalar_t__) ; 

__attribute__((used)) static
BOOL
ParseHour(
    PWSTR pszString,
    PWSTR *AmPmArray,
    PLONG plHour)
{
    PWCHAR pChar;
    LONG lHour = 0;

    if (!iswdigit(pszString[0]))
        return FALSE;

    pChar = pszString;
    while (iswdigit(*pChar))
    {
        lHour = lHour * 10 + *pChar - L'0';
        pChar++;
    }

    if (lHour > 24)
        return FALSE;

    if (lHour == 24)
        lHour = 0;

    if ((*pChar != UNICODE_NULL) &&
        (lHour >= 1) &&
        (lHour <= 12))
    {
        if ((_wcsicmp(pChar, AmPmArray[0]) == 0) ||
            (_wcsicmp(pChar, AmPmArray[1]) == 0))
        {
            if (lHour == 12)
                lHour = 0;
        }
        else if ((_wcsicmp(pChar, AmPmArray[2]) == 0) ||
                 (_wcsicmp(pChar, AmPmArray[3]) == 0))
        {
            if (lHour != 12)
                lHour += 12;
        }
        else
        {
            return FALSE;
        }
    }

    *plHour = lHour;

    return TRUE;
}