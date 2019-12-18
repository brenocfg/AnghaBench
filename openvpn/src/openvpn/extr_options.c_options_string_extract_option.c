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
struct gc_arena {int dummy; } ;

/* Variables and functions */
 char* gc_malloc (size_t,int,struct gc_arena*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t const) ; 

char *
options_string_extract_option(const char *options_string,const char *opt_name,
                              struct gc_arena *gc)
{
    char *ret = NULL;
    const size_t opt_name_len = strlen(opt_name);

    const char *p = options_string;
    while (p)
    {
        if (0 == strncmp(p, opt_name, opt_name_len)
            && strlen(p) > (opt_name_len+1) && p[opt_name_len] == ' ')
        {
            /* option found, extract value */
            const char *start = &p[opt_name_len+1];
            const char *end = strchr(p, ',');
            size_t val_len = end ? end - start : strlen(start);
            ret = gc_malloc(val_len+1, true, gc);
            memcpy(ret, start, val_len);
            break;
        }
        p = strchr(p, ',');
        if (p)
        {
            p++; /* skip delimiter */
        }
    }
    return ret;
}