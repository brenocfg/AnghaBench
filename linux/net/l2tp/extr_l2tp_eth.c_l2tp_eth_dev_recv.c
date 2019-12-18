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
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct l2tp_session {int debug; int /*<<< orphan*/  name; } ;
struct l2tp_eth_sess {int /*<<< orphan*/  dev; } ;
struct l2tp_eth {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 unsigned int ETH_HLEN ; 
 int L2TP_MSG_DATA ; 
 scalar_t__ NET_RX_SUCCESS ; 
 int /*<<< orphan*/  atomic_long_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ dev_forward_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct l2tp_eth_sess* l2tp_session_priv (struct l2tp_session*) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 struct l2tp_eth* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  secpath_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 

__attribute__((used)) static void l2tp_eth_dev_recv(struct l2tp_session *session, struct sk_buff *skb, int data_len)
{
	struct l2tp_eth_sess *spriv = l2tp_session_priv(session);
	struct net_device *dev;
	struct l2tp_eth *priv;

	if (session->debug & L2TP_MSG_DATA) {
		unsigned int length;

		length = min(32u, skb->len);
		if (!pskb_may_pull(skb, length))
			goto error;

		pr_debug("%s: eth recv\n", session->name);
		print_hex_dump_bytes("", DUMP_PREFIX_OFFSET, skb->data, length);
	}

	if (!pskb_may_pull(skb, ETH_HLEN))
		goto error;

	secpath_reset(skb);

	/* checksums verified by L2TP */
	skb->ip_summed = CHECKSUM_NONE;

	skb_dst_drop(skb);
	nf_reset_ct(skb);

	rcu_read_lock();
	dev = rcu_dereference(spriv->dev);
	if (!dev)
		goto error_rcu;

	priv = netdev_priv(dev);
	if (dev_forward_skb(dev, skb) == NET_RX_SUCCESS) {
		atomic_long_inc(&priv->rx_packets);
		atomic_long_add(data_len, &priv->rx_bytes);
	} else {
		atomic_long_inc(&priv->rx_errors);
	}
	rcu_read_unlock();

	return;

error_rcu:
	rcu_read_unlock();
error:
	kfree_skb(skb);
}