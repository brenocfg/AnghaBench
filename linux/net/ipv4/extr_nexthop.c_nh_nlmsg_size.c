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
struct nexthop {scalar_t__ is_group; } ;

/* Variables and functions */
 scalar_t__ nh_nlmsg_size_grp (struct nexthop*) ; 
 scalar_t__ nh_nlmsg_size_single (struct nexthop*) ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t nh_nlmsg_size(struct nexthop *nh)
{
	size_t sz = nla_total_size(4);    /* NHA_ID */

	if (nh->is_group)
		sz += nh_nlmsg_size_grp(nh);
	else
		sz += nh_nlmsg_size_single(nh);

	return sz;
}