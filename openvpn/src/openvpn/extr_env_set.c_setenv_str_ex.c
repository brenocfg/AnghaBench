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
 int /*<<< orphan*/  ASSERT (struct env_set*) ; 
 int /*<<< orphan*/  M_INFO ; 
 char* construct_name_value (char const*,char const*,struct gc_arena*) ; 
 int /*<<< orphan*/  env_set_add (struct env_set*,char const*) ; 
 int /*<<< orphan*/  env_set_del (struct env_set*,char const*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char const*) ; 
 char* string_mod_const (char const*,unsigned int const,unsigned int const,char const,struct gc_arena*) ; 
 int strlen (char const*) ; 

void
setenv_str_ex(struct env_set *es,
              const char *name,
              const char *value,
              const unsigned int name_include,
              const unsigned int name_exclude,
              const char name_replace,
              const unsigned int value_include,
              const unsigned int value_exclude,
              const char value_replace)
{
    struct gc_arena gc = gc_new();
    const char *name_tmp;
    const char *val_tmp = NULL;

    ASSERT(name && strlen(name) > 1);

    name_tmp = string_mod_const(name, name_include, name_exclude, name_replace, &gc);

    if (value)
    {
        val_tmp = string_mod_const(value, value_include, value_exclude, value_replace, &gc);
    }

    ASSERT(es);

    if (val_tmp)
    {
        const char *str = construct_name_value(name_tmp, val_tmp, &gc);
        env_set_add(es, str);
#if DEBUG_VERBOSE_SETENV
        msg(M_INFO, "SETENV_ES '%s'", str);
#endif
    }
    else
    {
        env_set_del(es, name_tmp);
    }

    gc_free(&gc);
}