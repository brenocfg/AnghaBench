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
struct route_ipv6_list {struct route_ipv6* routes_ipv6; } ;
struct route_ipv6 {struct route_ipv6* next; } ;
struct env_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  setenv_route_ipv6 (struct env_set*,struct route_ipv6*,int /*<<< orphan*/ ) ; 

void
setenv_routes_ipv6(struct env_set *es, const struct route_ipv6_list *rl6)
{
    int i = 1;
    struct route_ipv6 *r6;
    for (r6 = rl6->routes_ipv6; r6; r6 = r6->next)
    {
        setenv_route_ipv6(es, r6, i++);
    }
}