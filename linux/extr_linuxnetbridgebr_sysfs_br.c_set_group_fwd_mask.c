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
struct net_bridge {unsigned long group_fwd_mask; } ;

/* Variables and functions */
 unsigned long BR_GROUPFWD_RESTRICTED ; 
 int EINVAL ; 

__attribute__((used)) static int set_group_fwd_mask(struct net_bridge *br, unsigned long val)
{
	if (val & BR_GROUPFWD_RESTRICTED)
		return -EINVAL;

	br->group_fwd_mask = val;

	return 0;
}