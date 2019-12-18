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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int tx_bytes; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; } ;
struct l2cap_chan {struct sk_buff* data; } ;
struct kvec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,int /*<<< orphan*/ ) ; 
 int l2cap_chan_send (struct l2cap_chan*,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int send_pkt(struct l2cap_chan *chan, struct sk_buff *skb,
		    struct net_device *netdev)
{
	struct msghdr msg;
	struct kvec iv;
	int err;

	/* Remember the skb so that we can send EAGAIN to the caller if
	 * we run out of credits.
	 */
	chan->data = skb;

	iv.iov_base = skb->data;
	iv.iov_len = skb->len;

	memset(&msg, 0, sizeof(msg));
	iov_iter_kvec(&msg.msg_iter, WRITE, &iv, 1, skb->len);

	err = l2cap_chan_send(chan, &msg, skb->len);
	if (err > 0) {
		netdev->stats.tx_bytes += err;
		netdev->stats.tx_packets++;
		return 0;
	}

	if (err < 0)
		netdev->stats.tx_errors++;

	return err;
}