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
struct argv {scalar_t__ argv; } ;

/* Variables and functions */
 char const* print_argv (char const**,struct gc_arena*,unsigned int const) ; 

const char *
argv_str(const struct argv *a, struct gc_arena *gc, const unsigned int flags)
{
    if (a->argv)
    {
        return print_argv((const char **)a->argv, gc, flags);
    }
    else
    {
        return "";
    }
}