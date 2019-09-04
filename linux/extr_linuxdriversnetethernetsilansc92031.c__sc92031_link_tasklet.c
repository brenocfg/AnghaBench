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
struct TYPE_2__ {int /*<<< orphan*/  tx_carrier_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ _sc92031_check_media (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void _sc92031_link_tasklet(struct net_device *dev)
{
	if (_sc92031_check_media(dev))
		netif_wake_queue(dev);
	else {
		netif_stop_queue(dev);
		dev->stats.tx_carrier_errors++;
	}
}