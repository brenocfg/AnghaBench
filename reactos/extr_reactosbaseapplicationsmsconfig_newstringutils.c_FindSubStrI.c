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
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/ * LPCTSTR ;

/* Variables and functions */
 scalar_t__ _totupper (scalar_t__) ; 

LPTSTR FindSubStrI(LPCTSTR str, LPCTSTR strSearch)
{
    LPTSTR cp = (LPTSTR)str;
    LPTSTR s1, s2;

    if (!*strSearch)
        return (LPTSTR)str;

    while (*cp)
    {
        s1 = cp;
        s2 = (LPTSTR)strSearch;

        while (*s1 && *s2 && (_totupper(*s1) == _totupper(*s2)))
            ++s1, ++s2;

        if (!*s2)
            return cp;

        ++cp;
    }

    return NULL;
}