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
struct emac_priv {int /*<<< orphan*/  rx_buf_size; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 scalar_t__ WARN_ON (int) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *emac_rx_alloc(struct emac_priv *priv)
{
	struct sk_buff *skb = netdev_alloc_skb(priv->ndev, priv->rx_buf_size);
	if (WARN_ON(!skb))
		return NULL;
	skb_reserve(skb, NET_IP_ALIGN);
	return skb;
}