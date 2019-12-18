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
typedef  scalar_t__ TCHAR ;
typedef  scalar_t__* LPTSTR ;
typedef  scalar_t__* LPTCH ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ _totlower (scalar_t__) ; 

__attribute__((used)) static INT
IsKeyInString (LPTSTR lpString, TCHAR cKey, BOOL bCaseSensitive)
{
    LPTCH p = lpString;
    INT val = 0;

    while (*p)
    {
        if (bCaseSensitive)
        {
            if (*p == cKey)
                return val;
        }
        else
        {
            if (_totlower (*p) == _totlower (cKey))
                return val;
        }

        val++;
        p++;
    }

    return -1;
}