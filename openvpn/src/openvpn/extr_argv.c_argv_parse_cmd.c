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
struct argv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ARGV_PARSE_CMD ; 
 int /*<<< orphan*/  MAX_PARMS ; 
 int /*<<< orphan*/  argv_append (struct argv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_extend (struct argv*,int) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int parse_line (char const*,char**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  string_alloc (char const*,int /*<<< orphan*/ *) ; 

void
argv_parse_cmd(struct argv *a, const char *s)
{
    int nparms;
    char *parms[MAX_PARMS + 1];
    struct gc_arena gc = gc_new();

    argv_reset(a);
    argv_extend(a, 1); /* ensure trailing NULL */

    nparms = parse_line(s, parms, MAX_PARMS, "SCRIPT-ARGV", 0, D_ARGV_PARSE_CMD, &gc);
    if (nparms)
    {
        int i;
        for (i = 0; i < nparms; ++i)
        {
            argv_append(a, string_alloc(parms[i], NULL));
        }
    }
    else
    {
        argv_append(a, string_alloc(s, NULL));
    }

    gc_free(&gc);
}