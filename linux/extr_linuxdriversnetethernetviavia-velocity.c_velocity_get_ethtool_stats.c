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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct velocity_info {int /*<<< orphan*/  lock; int /*<<< orphan*/ * mib_counter; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  velocity_gstrings ; 
 int /*<<< orphan*/  velocity_update_hw_mibs (struct velocity_info*) ; 

__attribute__((used)) static void velocity_get_ethtool_stats(struct net_device *dev,
				       struct ethtool_stats *stats, u64 *data)
{
	if (netif_running(dev)) {
		struct velocity_info *vptr = netdev_priv(dev);
		u32 *p = vptr->mib_counter;
		int i;

		spin_lock_irq(&vptr->lock);
		velocity_update_hw_mibs(vptr);
		spin_unlock_irq(&vptr->lock);

		for (i = 0; i < ARRAY_SIZE(velocity_gstrings); i++)
			*data++ = *p++;
	}
}