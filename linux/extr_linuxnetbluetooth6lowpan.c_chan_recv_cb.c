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
struct sk_buff {int dummy; } ;
struct lowpan_peer {int dummy; } ;
struct lowpan_btle_dev {int /*<<< orphan*/  netdev; } ;
struct l2cap_chan {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int) ; 
 int EAGAIN ; 
 int ENOENT ; 
 struct lowpan_btle_dev* lookup_dev (int /*<<< orphan*/ ) ; 
 struct lowpan_peer* lookup_peer (int /*<<< orphan*/ ) ; 
 int recv_pkt (struct sk_buff*,int /*<<< orphan*/ ,struct lowpan_peer*) ; 

__attribute__((used)) static int chan_recv_cb(struct l2cap_chan *chan, struct sk_buff *skb)
{
	struct lowpan_btle_dev *dev;
	struct lowpan_peer *peer;
	int err;

	peer = lookup_peer(chan->conn);
	if (!peer)
		return -ENOENT;

	dev = lookup_dev(chan->conn);
	if (!dev || !dev->netdev)
		return -ENOENT;

	err = recv_pkt(skb, dev->netdev, peer);
	if (err) {
		BT_DBG("recv pkt %d", err);
		err = -EAGAIN;
	}

	return err;
}