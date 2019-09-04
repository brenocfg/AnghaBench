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
typedef  void* u32 ;
struct sk_buff {void* len; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct lec_priv {void* sizeoftlvs; int /*<<< orphan*/ * tlvs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* alloc_skb (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l_associate_req ; 
 struct lec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int send_to_lecd (struct lec_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/  const*,void*) ; 

__attribute__((used)) static int lane2_associate_req(struct net_device *dev, const u8 *lan_dst,
			       const u8 *tlvs, u32 sizeoftlvs)
{
	int retval;
	struct sk_buff *skb;
	struct lec_priv *priv = netdev_priv(dev);

	if (!ether_addr_equal(lan_dst, dev->dev_addr))
		return 0;	/* not our mac address */

	kfree(priv->tlvs);	/* NULL if there was no previous association */

	priv->tlvs = kmemdup(tlvs, sizeoftlvs, GFP_KERNEL);
	if (priv->tlvs == NULL)
		return 0;
	priv->sizeoftlvs = sizeoftlvs;

	skb = alloc_skb(sizeoftlvs, GFP_ATOMIC);
	if (skb == NULL)
		return 0;
	skb->len = sizeoftlvs;
	skb_copy_to_linear_data(skb, tlvs, sizeoftlvs);
	retval = send_to_lecd(priv, l_associate_req, NULL, NULL, skb);
	if (retval != 0)
		pr_info("lec.c: lane2_associate_req() failed\n");
	/*
	 * If the previous association has changed we must
	 * somehow notify other LANE entities about the change
	 */
	return 1;
}