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
struct route_ipv6_option_list {struct gc_arena* gc; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */

void
copy_route_ipv6_option_list(struct route_ipv6_option_list *dest,
                            const struct route_ipv6_option_list *src,
                            struct gc_arena *a)
{
    *dest = *src;
    dest->gc = a;
}