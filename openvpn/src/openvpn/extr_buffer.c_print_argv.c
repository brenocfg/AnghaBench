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
struct buffer {int dummy; } ;

/* Variables and functions */
 char* BSTR (struct buffer*) ; 
 unsigned int const PA_BRACKET ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,...) ; 

char *
print_argv(const char **p, struct gc_arena *gc, const unsigned int flags)
{
    struct buffer out = alloc_buf_gc(256, gc);
    int i = 0;
    for (;; )
    {
        const char *cp = *p++;
        if (!cp)
        {
            break;
        }
        if (i)
        {
            buf_printf(&out, " ");
        }
        if (flags & PA_BRACKET)
        {
            buf_printf(&out, "[%s]", cp);
        }
        else
        {
            buf_printf(&out, "%s", cp);
        }
        ++i;
    }
    return BSTR(&out);
}