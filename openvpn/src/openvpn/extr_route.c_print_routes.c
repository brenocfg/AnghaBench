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
struct route_list {struct route_ipv4* routes; } ;
struct route_ipv4 {struct route_ipv4* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_route (struct route_ipv4*,int) ; 

void
print_routes(const struct route_list *rl, int level)
{
    struct route_ipv4 *r;
    for (r = rl->routes; r; r = r->next)
    {
        print_route(r, level);
    }
}