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

/* Variables and functions */

__attribute__((used)) static bool
get_key_value(const char *str,       /* source string */
              char *key,             /* key stored here */
              char *value,           /* value stored here */
              int max_key_len,
              int max_value_len,
              const char **endptr)   /* next search position */
{
    int c;
    bool starts_with_quote = false;
    bool escape = false;

    for (c = max_key_len-1; (*str && (*str != '=') && c--); )
    {
        *key++ = *str++;
    }
    *key = '\0';

    if ('=' != *str++)
    {
        /* no key/value found */
        return false;
    }

    if ('\"' == *str)
    {
        /* quoted string */
        str++;
        starts_with_quote = true;
    }

    for (c = max_value_len-1; *str && c--; str++)
    {
        switch (*str)
        {
            case '\\':
                if (!escape)
                {
                    /* possibly the start of an escaped quote */
                    escape = true;
                    *value++ = '\\'; /* even though this is an escape character, we still
                                      * store it as-is in the target buffer */
                    continue;
                }
                break;

            case ',':
                if (!starts_with_quote)
                {
                    /* this signals the end of the value if we didn't get a starting quote
                     * and then we do "sloppy" parsing */
                    c = 0; /* the end */
                    continue;
                }
                break;

            case '\r':
            case '\n':
                /* end of string */
                c = 0;
                continue;

            case '\"':
                if (!escape && starts_with_quote)
                {
                    /* end of string */
                    c = 0;
                    continue;
                }
                break;
        }
        escape = false;
        *value++ = *str;
    }
    *value = '\0';

    *endptr = str;

    return true; /* success */
}