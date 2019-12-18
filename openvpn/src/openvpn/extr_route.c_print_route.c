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
struct route_ipv4 {int flags; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int RT_DEFINED ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  route_string (struct route_ipv4 const*,struct gc_arena*) ; 

__attribute__((used)) static void
print_route(const struct route_ipv4 *r, int level)
{
    struct gc_arena gc = gc_new();
    if (r->flags & RT_DEFINED)
    {
        msg(level, "%s", route_string(r, &gc));
    }
    gc_free(&gc);
}