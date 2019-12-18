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
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ _T (char) ; 
 scalar_t__ _istspace (scalar_t__) ; 

__attribute__((used)) static TCHAR *GetParameter(TCHAR **pPointer)
{
    BOOL bInQuote = FALSE;
    TCHAR *start = *pPointer;
    TCHAR *p;
    for (p = start; *p; p++)
    {
        if (!bInQuote && (*p == _T('/') || _istspace(*p)))
            break;
        bInQuote ^= (*p == _T('"'));
        p[-1] = *p;
    }
    p[-1] = _T('\0');
    *pPointer = p;
    return start - 1;
}