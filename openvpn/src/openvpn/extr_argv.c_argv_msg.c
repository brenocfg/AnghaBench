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
 int /*<<< orphan*/  argv_str (struct argv const*,struct gc_arena*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int const,char*,int /*<<< orphan*/ ) ; 

void
argv_msg(const int msglev, const struct argv *a)
{
    struct gc_arena gc = gc_new();
    msg(msglev, "%s", argv_str(a, &gc, 0));
    gc_free(&gc);
}