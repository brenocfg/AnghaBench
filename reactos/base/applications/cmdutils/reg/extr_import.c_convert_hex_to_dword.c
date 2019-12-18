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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ isxdigitW (char) ; 
 int /*<<< orphan*/  strtoulW (char*,char**,int) ; 

__attribute__((used)) static BOOL convert_hex_to_dword(WCHAR *str, DWORD *dw)
{
    WCHAR *p, *end;
    int count = 0;

    while (*str == ' ' || *str == '\t') str++;
    if (!*str) goto error;

    p = str;
    while (isxdigitW(*p))
    {
        count++;
        p++;
    }
    if (count > 8) goto error;

    end = p;
    while (*p == ' ' || *p == '\t') p++;
    if (*p && *p != ';') goto error;

    *end = 0;
    *dw = strtoulW(str, &end, 16);
    return TRUE;

error:
    return FALSE;
}