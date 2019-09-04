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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct lec_priv {int /*<<< orphan*/  lec_arp_lock; } ;
struct lec_arp_table {int /*<<< orphan*/  sizeoftlvs; int /*<<< orphan*/  tlvs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l_arp_xmt ; 
 struct lec_arp_table* lec_arp_find (struct lec_priv*,int /*<<< orphan*/  const*) ; 
 struct lec_priv* netdev_priv (struct net_device*) ; 
 int send_to_lecd (struct lec_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int lane2_resolve(struct net_device *dev, const u8 *dst_mac, int force,
			 u8 **tlvs, u32 *sizeoftlvs)
{
	unsigned long flags;
	struct lec_priv *priv = netdev_priv(dev);
	struct lec_arp_table *table;
	struct sk_buff *skb;
	int retval;

	if (force == 0) {
		spin_lock_irqsave(&priv->lec_arp_lock, flags);
		table = lec_arp_find(priv, dst_mac);
		spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
		if (table == NULL)
			return -1;

		*tlvs = kmemdup(table->tlvs, table->sizeoftlvs, GFP_ATOMIC);
		if (*tlvs == NULL)
			return -1;

		*sizeoftlvs = table->sizeoftlvs;

		return 0;
	}

	if (sizeoftlvs == NULL)
		retval = send_to_lecd(priv, l_arp_xmt, dst_mac, NULL, NULL);

	else {
		skb = alloc_skb(*sizeoftlvs, GFP_ATOMIC);
		if (skb == NULL)
			return -1;
		skb->len = *sizeoftlvs;
		skb_copy_to_linear_data(skb, *tlvs, *sizeoftlvs);
		retval = send_to_lecd(priv, l_arp_xmt, dst_mac, NULL, skb);
	}
	return retval;
}