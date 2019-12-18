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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int strlen (char*) ; 

char *trim(char *str, char **last_chr, BOOL strip_quotes)
{
    char *last;

    for (; *str; str++)
    {
        if (*str != '\t' && *str != ' ')
            break;
    }

    if (!*str)
    {
        if (last_chr) *last_chr = str;
        return str;
    }

    last = str + strlen(str) - 1;

    for (; last > str; last--)
    {
        if (*last != '\t' && *last != ' ')
            break;
        *last = 0;
    }

    if (strip_quotes && last != str)
    {
        if (*last == '"' && *str == '"')
        {
            str++;
            *last = 0;
        }
    }

    if (last_chr) *last_chr = last;
    return str;
}