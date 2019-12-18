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
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,int /*<<< orphan*/ ,struct lowpan_btle_dev*) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  add_peer_chan (struct l2cap_chan*,struct lowpan_btle_dev*,int) ; 
 int /*<<< orphan*/  ifup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 struct lowpan_btle_dev* lookup_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ setup_netdev (struct l2cap_chan*,struct lowpan_btle_dev**) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void chan_ready_cb(struct l2cap_chan *chan)
{
	struct lowpan_btle_dev *dev;
	bool new_netdev = false;

	dev = lookup_dev(chan->conn);

	BT_DBG("chan %p conn %p dev %p", chan, chan->conn, dev);

	if (!dev) {
		if (setup_netdev(chan, &dev) < 0) {
			l2cap_chan_del(chan, -ENOENT);
			return;
		}
		new_netdev = true;
	}

	if (!try_module_get(THIS_MODULE))
		return;

	add_peer_chan(chan, dev, new_netdev);
	ifup(dev->netdev);
}