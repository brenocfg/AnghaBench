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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 char* strdupA (char const*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *unquote_string(const char *str)
{
    BOOL quoted = FALSE;
    char *ret, *cp;

    while(*str == ' ' || *str == '\t') str++;

    if(*str == '"')
    {
        quoted = TRUE;
        str++;
    }
    ret = strdupA(str);
    for(cp = ret; *cp; cp++)
    {
        if(*cp == '\\')
            memmove(cp, cp + 1, strlen(cp + 1) + 1);
        else if(*cp == '"')
        {
            if(!quoted)
            {
                WARN("quote in unquoted string\n");
            }
            else
            {
                *cp = '\0';
                break;
            }
        }
    }
    return ret;
}