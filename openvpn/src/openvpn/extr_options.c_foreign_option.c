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
struct options {char* foreign_option_index; } ;
struct gc_arena {int dummy; } ;
struct env_set {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR (struct buffer*) ; 
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  OPTION_PARM_SIZE ; 
 struct buffer alloc_buf_gc (int /*<<< orphan*/ ,struct gc_arena*) ; 
 int buf_printf (struct buffer*,char*,...) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
foreign_option(struct options *o, char *argv[], int len, struct env_set *es)
{
    if (len > 0)
    {
        struct gc_arena gc = gc_new();
        struct buffer name = alloc_buf_gc(OPTION_PARM_SIZE, &gc);
        struct buffer value = alloc_buf_gc(OPTION_PARM_SIZE, &gc);
        int i;
        bool first = true;
        bool good = true;

        good &= buf_printf(&name, "foreign_option_%d", o->foreign_option_index + 1);
        ++o->foreign_option_index;
        for (i = 0; i < len; ++i)
        {
            if (argv[i])
            {
                if (!first)
                {
                    good &= buf_printf(&value, " ");
                }
                good &= buf_printf(&value, "%s", argv[i]);
                first = false;
            }
        }
        if (good)
        {
            setenv_str(es, BSTR(&name), BSTR(&value));
        }
        else
        {
            msg(M_WARN, "foreign_option: name/value overflow");
        }
        gc_free(&gc);
    }
}