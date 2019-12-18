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
struct options {int /*<<< orphan*/  gc; scalar_t__ routes_ipv6; } ;

/* Variables and functions */
 scalar_t__ new_route_ipv6_option_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rol6_check_alloc(struct options *options)
{
    if (!options->routes_ipv6)
    {
        options->routes_ipv6 = new_route_ipv6_option_list(&options->gc);
    }
}