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
typedef  int* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int UNICODE_NULL ; 
 int wcslen (int*) ; 

LPWSTR MakeFilter(LPWSTR psz)
{
    WCHAR *pch;

    ASSERT(psz[0] != UNICODE_NULL &&
           psz[wcslen(psz) - 1] == L'|');
    for (pch = psz; *pch != UNICODE_NULL; pch++)
    {
        /* replace vertical bar with NULL */
        if (*pch == L'|')
        {
            *pch = UNICODE_NULL;
        }
    }
    return psz;
}