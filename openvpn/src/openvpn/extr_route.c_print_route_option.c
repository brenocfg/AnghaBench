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
struct route_option {int /*<<< orphan*/  metric; int /*<<< orphan*/  gateway; int /*<<< orphan*/  netmask; int /*<<< orphan*/  network; } ;

/* Variables and functions */
 int /*<<< orphan*/  msg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_opt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_route_option(const struct route_option *ro, int level)
{
    msg(level, "  route %s/%s/%s/%s",
        show_opt(ro->network),
        show_opt(ro->netmask),
        show_opt(ro->gateway),
        show_opt(ro->metric));
}