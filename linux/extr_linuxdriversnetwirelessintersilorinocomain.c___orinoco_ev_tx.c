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
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct hermes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_FID ; 
 int /*<<< orphan*/  TXCOMPLFID ; 
 int /*<<< orphan*/  hermes_write_regn (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void __orinoco_ev_tx(struct net_device *dev, struct hermes *hw)
{
	dev->stats.tx_packets++;

	netif_wake_queue(dev);

	hermes_write_regn(hw, TXCOMPLFID, DUMMY_FID);
}