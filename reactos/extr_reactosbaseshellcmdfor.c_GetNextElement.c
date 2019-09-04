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
 int TRUE ; 
 scalar_t__ _T (char) ; 
 scalar_t__ _istspace (scalar_t__) ; 

__attribute__((used)) static BOOL GetNextElement(TCHAR **pStart, TCHAR **pEnd)
{
    TCHAR *p = *pEnd;
    BOOL InQuotes = FALSE;
    while (_istspace(*p))
        p++;
    if (!*p)
        return FALSE;
    *pStart = p;
    while (*p && (InQuotes || !_istspace(*p)))
        InQuotes ^= (*p++ == _T('"'));
    *pEnd = p;
    return TRUE;
}