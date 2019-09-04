#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct TYPE_2__ {int hw_resetting; int hw_ready; scalar_t__ hw_reset_tries; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384X_CMDCODE_ENABLE ; 
 scalar_t__ hfa384x_cmd (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfa384x_enable_interrupts (struct net_device*) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ prism2_reset_port (struct net_device*) ; 

__attribute__((used)) static int prism2_hw_enable(struct net_device *dev, int initial)
{
	struct hostap_interface *iface;
	local_info_t *local;
	int was_resetting;

	iface = netdev_priv(dev);
	local = iface->local;
	was_resetting = local->hw_resetting;

	if (hfa384x_cmd(dev, HFA384X_CMDCODE_ENABLE, 0, NULL, NULL)) {
		printk("%s: MAC port 0 enabling failed\n", dev->name);
		return 1;
	}

	local->hw_ready = 1;
	local->hw_reset_tries = 0;
	local->hw_resetting = 0;
	hfa384x_enable_interrupts(dev);

	/* at least D-Link DWL-650 seems to require additional port reset
	 * before it starts acting as an AP, so reset port automatically
	 * here just in case */
	if (initial && prism2_reset_port(dev)) {
		printk("%s: MAC port 0 resetting failed\n", dev->name);
		return 1;
	}

	if (was_resetting && netif_queue_stopped(dev)) {
		/* If hw_reset() was called during pending transmit, netif
		 * queue was stopped. Wake it up now since the wlan card has
		 * been resetted. */
		netif_wake_queue(dev);
	}

	return 0;
}