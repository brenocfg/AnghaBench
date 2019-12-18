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
 char* string_alloc (char const*,struct gc_arena*) ; 
 int /*<<< orphan*/  string_mod (char*,unsigned int const,unsigned int const,char const) ; 

const char *
string_mod_const(const char *str,
                 const unsigned int inclusive,
                 const unsigned int exclusive,
                 const char replace,
                 struct gc_arena *gc)
{
    if (str)
    {
        char *buf = string_alloc(str, gc);
        string_mod(buf, inclusive, exclusive, replace);
        return buf;
    }
    else
    {
        return NULL;
    }
}