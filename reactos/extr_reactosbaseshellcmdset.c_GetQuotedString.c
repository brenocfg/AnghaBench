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

/* Variables and functions */
 scalar_t__ _T (char) ; 
 scalar_t__* _tcsrchr (scalar_t__*,scalar_t__) ; 
 scalar_t__ skip_ws (scalar_t__*) ; 

__attribute__((used)) static LPTSTR
GetQuotedString(TCHAR *p)
{
    TCHAR *end;
    if (*p == _T('"'))
    {
        p = (LPTSTR)skip_ws(p + 1);
        /* If a matching quote is found, truncate the string */
        end = _tcsrchr(p, _T('"'));
        if (end)
            *end = _T('\0');
    }
    return p;
}