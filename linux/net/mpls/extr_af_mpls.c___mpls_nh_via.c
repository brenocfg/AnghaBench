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
typedef  int /*<<< orphan*/  u8 ;
struct mpls_route {int rt_via_offset; } ;
struct mpls_nh {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u8 *__mpls_nh_via(struct mpls_route *rt, struct mpls_nh *nh)
{
	return (u8 *)nh + rt->rt_via_offset;
}