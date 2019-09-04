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
typedef  int /*<<< orphan*/  u16 ;
struct rhine_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  active_vlans; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct rhine_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rhine_update_vcam (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rhine_vlan_rx_add_vid(struct net_device *dev, __be16 proto, u16 vid)
{
	struct rhine_private *rp = netdev_priv(dev);

	spin_lock_bh(&rp->lock);
	set_bit(vid, rp->active_vlans);
	rhine_update_vcam(dev);
	spin_unlock_bh(&rp->lock);
	return 0;
}