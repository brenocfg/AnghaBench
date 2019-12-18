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
 int /*<<< orphan*/  D_SHOW_KEYS ; 
 int /*<<< orphan*/  check_debug_level (int /*<<< orphan*/ ) ; 
 char* gc_malloc (scalar_t__,int,struct gc_arena*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

const char *
sanitize_control_message(const char *src, struct gc_arena *gc)
{
    char *ret = gc_malloc(strlen(src)+1, false, gc);
    char *dest = ret;
    bool redact = false;
    int skip = 0;

    for (;; )
    {
        const char c = *src;
        if (c == '\0')
        {
            break;
        }
        if (c == 'S' && !strncmp(src, "SESS_ID_", 8))
        {
            skip = 7;
            redact = true;
        }
        else if (c == 'e' && !strncmp(src, "echo ", 5))
        {
            skip = 4;
            redact = true;
        }
        else if (!check_debug_level(D_SHOW_KEYS)
                 && (c == 'a' && !strncmp(src, "auth-token ", 11)))
        {
            /* Unless --verb is 7 or higher (D_SHOW_KEYS), hide
             * the auth-token value coming in the src string
             */
            skip = 10;
            redact = true;
        }

        if (c == ',') /* end of redacted item? */
        {
            skip = 0;
            redact = false;
        }

        if (redact)
        {
            if (skip > 0)
            {
                --skip;
                *dest++ = c;
            }
        }
        else
        {
            *dest++ = c;
        }

        ++src;
    }
    *dest = '\0';
    return ret;
}