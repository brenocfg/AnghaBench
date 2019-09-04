#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ expires; } ;
struct TYPE_4__ {scalar_t__ loopback_mode; } ;
struct niu {TYPE_2__ timer; TYPE_1__ link_config; int /*<<< orphan*/  lock; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int ETH_DATA_LEN ; 
 scalar_t__ HZ ; 
 scalar_t__ LOOPBACK_DISABLED ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int niu_alloc_channels (struct niu*) ; 
 int niu_enable_interrupts (struct niu*,int) ; 
 int /*<<< orphan*/  niu_enable_napi (struct niu*) ; 
 int /*<<< orphan*/  niu_free_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_full_shutdown (struct niu*,struct net_device*) ; 
 int niu_init_hw (struct niu*) ; 
 int /*<<< orphan*/  niu_stop_hw (struct niu*) ; 
 int /*<<< orphan*/  niu_timer ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_change_mtu(struct net_device *dev, int new_mtu)
{
	struct niu *np = netdev_priv(dev);
	int err, orig_jumbo, new_jumbo;

	orig_jumbo = (dev->mtu > ETH_DATA_LEN);
	new_jumbo = (new_mtu > ETH_DATA_LEN);

	dev->mtu = new_mtu;

	if (!netif_running(dev) ||
	    (orig_jumbo == new_jumbo))
		return 0;

	niu_full_shutdown(np, dev);

	niu_free_channels(np);

	niu_enable_napi(np);

	err = niu_alloc_channels(np);
	if (err)
		return err;

	spin_lock_irq(&np->lock);

	err = niu_init_hw(np);
	if (!err) {
		timer_setup(&np->timer, niu_timer, 0);
		np->timer.expires = jiffies + HZ;

		err = niu_enable_interrupts(np, 1);
		if (err)
			niu_stop_hw(np);
	}

	spin_unlock_irq(&np->lock);

	if (!err) {
		netif_tx_start_all_queues(dev);
		if (np->link_config.loopback_mode != LOOPBACK_DISABLED)
			netif_carrier_on(dev);

		add_timer(&np->timer);
	}

	return err;
}