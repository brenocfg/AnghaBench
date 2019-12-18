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
struct env_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 char* setenv_format_indexed_name (char const*,int const,struct gc_arena*) ; 
 int /*<<< orphan*/  setenv_int (struct env_set*,char const*,int const) ; 

void
setenv_int_i(struct env_set *es, const char *name, const int value, const int i)
{
    struct gc_arena gc = gc_new();
    const char *name_str = setenv_format_indexed_name(name, i, &gc);
    setenv_int(es, name_str, value);
    gc_free(&gc);
}