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
struct net_bridge {unsigned long vlan_stats_enabled; } ;

/* Variables and functions */
 int EINVAL ; 

int br_vlan_set_stats(struct net_bridge *br, unsigned long val)
{
	switch (val) {
	case 0:
	case 1:
		br->vlan_stats_enabled = val;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}