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
struct sk_buff {unsigned int len; int /*<<< orphan*/  dev; } ;
struct qmimux_priv {int /*<<< orphan*/  real_dev; int /*<<< orphan*/  mux_id; } ;
struct qmimux_hdr {int /*<<< orphan*/  pkt_len; int /*<<< orphan*/  mux_id; scalar_t__ pad; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 struct qmimux_priv* netdev_priv (struct net_device*) ; 
 struct qmimux_hdr* skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static netdev_tx_t qmimux_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct qmimux_priv *priv = netdev_priv(dev);
	unsigned int len = skb->len;
	struct qmimux_hdr *hdr;

	hdr = skb_push(skb, sizeof(struct qmimux_hdr));
	hdr->pad = 0;
	hdr->mux_id = priv->mux_id;
	hdr->pkt_len = cpu_to_be16(len);
	skb->dev = priv->real_dev;
	return dev_queue_xmit(skb);
}