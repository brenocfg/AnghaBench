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
struct net_device {int ifindex; } ;

/* Variables and functions */

__attribute__((used)) static bool neigh_ifindex_filtered(struct net_device *dev, int filter_idx)
{
	if (filter_idx && dev->ifindex != filter_idx)
		return true;

	return false;
}