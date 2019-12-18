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
typedef  int /*<<< orphan*/  u8 ;
struct lowpan_peer {int /*<<< orphan*/  chan; } ;
struct l2cap_conn {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct lowpan_peer*,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  l2cap_chan_close (int /*<<< orphan*/ ,int) ; 
 struct lowpan_peer* lookup_peer (struct lowpan_peer*) ; 

__attribute__((used)) static int bt_6lowpan_disconnect(struct l2cap_conn *conn, u8 dst_type)
{
	struct lowpan_peer *peer;

	BT_DBG("conn %p dst type %d", conn, dst_type);

	peer = lookup_peer(conn);
	if (!peer)
		return -ENOENT;

	BT_DBG("peer %p chan %p", peer, peer->chan);

	l2cap_chan_close(peer->chan, ENOENT);

	return 0;
}