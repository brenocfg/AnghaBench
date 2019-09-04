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
typedef  int WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  wcsspn (int*,char*) ; 

__attribute__((used)) static BOOL GetArg(WCHAR **pStart, WCHAR **pEnd)
{
    BOOL bInQuotes = FALSE;
    WCHAR *p = *pEnd;
    p += wcsspn(p, L" \t");
    if (!*p)
        return FALSE;
    *pStart = p;
    do
    {
        if (!bInQuotes && (*p == L' ' || *p == L'\t'))
            break;
        bInQuotes ^= (*p++ == L'"');
    } while (*p);
    *pEnd = p;
    return TRUE;
}