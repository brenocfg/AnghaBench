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
 int /*<<< orphan*/  INLINE_FILE_TAG ; 
 char const** make_arg_array (char*,char*,struct gc_arena*) ; 
 char const** make_arg_copy (char**,struct gc_arena*) ; 
 char const** make_inline_array (char*,struct gc_arena*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int string_array_len (char const**) ; 

const char **
make_extended_arg_array(char **p, struct gc_arena *gc)
{
    const int argc = string_array_len((const char **)p);
    if (!strcmp(p[0], INLINE_FILE_TAG) && argc == 2)
    {
        return make_inline_array(p[1], gc);
    }
    else if (argc == 0)
    {
        return make_arg_array(NULL, NULL, gc);
    }
    else if (argc == 1)
    {
        return make_arg_array(p[0], NULL, gc);
    }
    else if (argc == 2)
    {
        return make_arg_array(p[0], p[1], gc);
    }
    else
    {
        return make_arg_copy(p, gc);
    }
}