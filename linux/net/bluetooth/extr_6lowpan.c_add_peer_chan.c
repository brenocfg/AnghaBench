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
struct lowpan_peer {struct l2cap_chan* chan; int /*<<< orphan*/  list; scalar_t__ lladdr; int /*<<< orphan*/  peer_addr; } ;
struct lowpan_btle_dev {int /*<<< orphan*/  notify_peers; } ;
struct l2cap_chan {int /*<<< orphan*/  dst; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  baswap (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devices_lock ; 
 int /*<<< orphan*/  do_notify_peers ; 
 struct lowpan_peer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lowpan_iphc_uncompress_eui48_lladdr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  peer_add (struct lowpan_btle_dev*,struct lowpan_peer*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct l2cap_chan *add_peer_chan(struct l2cap_chan *chan,
					struct lowpan_btle_dev *dev,
					bool new_netdev)
{
	struct lowpan_peer *peer;

	peer = kzalloc(sizeof(*peer), GFP_ATOMIC);
	if (!peer)
		return NULL;

	peer->chan = chan;
	memset(&peer->peer_addr, 0, sizeof(struct in6_addr));

	baswap((void *)peer->lladdr, &chan->dst);

	lowpan_iphc_uncompress_eui48_lladdr(&peer->peer_addr, peer->lladdr);

	spin_lock(&devices_lock);
	INIT_LIST_HEAD(&peer->list);
	peer_add(dev, peer);
	spin_unlock(&devices_lock);

	/* Notifying peers about us needs to be done without locks held */
	if (new_netdev)
		INIT_DELAYED_WORK(&dev->notify_peers, do_notify_peers);
	schedule_delayed_work(&dev->notify_peers, msecs_to_jiffies(100));

	return peer->chan;
}