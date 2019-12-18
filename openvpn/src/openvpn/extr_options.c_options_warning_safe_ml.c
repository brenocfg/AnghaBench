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
 scalar_t__ OPTION_PARM_SIZE ; 
 struct buffer alloc_buf_gc (scalar_t__,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char const*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  options_warning_safe_scan1 (int const,char,int,struct buffer*,struct buffer*,char*,char*) ; 

__attribute__((used)) static void
options_warning_safe_ml(const int msglevel, char *actual, const char *expected, size_t actual_n)
{
    struct gc_arena gc = gc_new();

    if (actual_n > 0)
    {
        struct buffer local = alloc_buf_gc(OPTION_PARM_SIZE + 16, &gc);
        struct buffer remote = alloc_buf_gc(OPTION_PARM_SIZE + 16, &gc);
        actual[actual_n - 1] = 0;

        buf_printf(&local, "version %s", expected);
        buf_printf(&remote, "version %s", actual);

        options_warning_safe_scan1(msglevel, ',', true,
                                   &local, &remote,
                                   "local", "remote");

        options_warning_safe_scan1(msglevel, ',', false,
                                   &remote, &local,
                                   "remote", "local");
    }

    gc_free(&gc);
}