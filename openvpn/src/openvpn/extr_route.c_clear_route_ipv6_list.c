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
struct route_ipv6_list {int /*<<< orphan*/  gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct route_ipv6_list) ; 
 int /*<<< orphan*/  gc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clear_route_ipv6_list(struct route_ipv6_list *rl6)
{
    gc_free(&rl6->gc);
    CLEAR(*rl6);
}