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
struct net_bridge {unsigned long multicast_igmp_version; int /*<<< orphan*/  multicast_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int br_multicast_set_igmp_version(struct net_bridge *br, unsigned long val)
{
	/* Currently we support only version 2 and 3 */
	switch (val) {
	case 2:
	case 3:
		break;
	default:
		return -EINVAL;
	}

	spin_lock_bh(&br->multicast_lock);
	br->multicast_igmp_version = val;
	spin_unlock_bh(&br->multicast_lock);

	return 0;
}