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
struct velocity_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  active_vlans; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  velocity_init_cam_filter (struct velocity_info*) ; 

__attribute__((used)) static int velocity_vlan_rx_add_vid(struct net_device *dev,
				    __be16 proto, u16 vid)
{
	struct velocity_info *vptr = netdev_priv(dev);

	spin_lock_irq(&vptr->lock);
	set_bit(vid, vptr->active_vlans);
	velocity_init_cam_filter(vptr);
	spin_unlock_irq(&vptr->lock);
	return 0;
}