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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ toupperW (char const) ; 

__attribute__((used)) static BOOL eval_like( const WCHAR *lstr, const WCHAR *rstr )
{
    const WCHAR *p = lstr, *q = rstr;

    while (*p && *q)
    {
        if (*q == '%')
        {
            while (*q == '%') q++;
            if (!*q) return TRUE;
            while (*p && *q && toupperW( *p ) == toupperW( *q )) { p++; q++; };
            if (!*p && !*q) return TRUE;
        }
        if (*q != '%' && toupperW( *p++ ) != toupperW( *q++ )) return FALSE;
    }
    return TRUE;
}