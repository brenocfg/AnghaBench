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
typedef  int u8 ;
struct mpls_route {int rt_nh_size; scalar_t__ rt_nh; } ;
struct mpls_nh {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct mpls_nh *mpls_get_nexthop(struct mpls_route *rt, u8 index)
{
	return (struct mpls_nh *)((u8 *)rt->rt_nh + index * rt->rt_nh_size);
}