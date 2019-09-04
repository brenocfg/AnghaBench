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
struct lowpan_btle_dev {int /*<<< orphan*/  netdev; } ;
struct l2cap_chan {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 struct lowpan_btle_dev* lookup_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chan_suspend_cb(struct l2cap_chan *chan)
{
	struct lowpan_btle_dev *dev;

	BT_DBG("chan %p suspend", chan);

	dev = lookup_dev(chan->conn);
	if (!dev || !dev->netdev)
		return;

	netif_stop_queue(dev->netdev);
}