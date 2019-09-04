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
struct net_bridge_port {unsigned long group_fwd_mask; } ;

/* Variables and functions */
 unsigned long BR_GROUPFWD_MACPAUSE ; 
 int EINVAL ; 

__attribute__((used)) static int store_group_fwd_mask(struct net_bridge_port *p,
				unsigned long v)
{
	if (v & BR_GROUPFWD_MACPAUSE)
		return -EINVAL;
	p->group_fwd_mask = v;

	return 0;
}