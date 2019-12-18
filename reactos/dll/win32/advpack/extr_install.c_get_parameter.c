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
typedef  char* LPWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 char* wcschr (char*,char) ; 

LPWSTR get_parameter(LPWSTR *params, WCHAR separator, BOOL quoted)
{
    LPWSTR token = *params;

    if (!*params)
        return NULL;

    if (quoted && *token == '"')
    {
        WCHAR *end = wcschr(token + 1, '"');
        if (end)
        {
            *end = 0;
            *params = end + 1;
            token = token + 1;
        }
    }

    *params = wcschr(*params, separator);
    if (*params)
        *(*params)++ = '\0';

    if (!*token)
        return NULL;

    return token;
}