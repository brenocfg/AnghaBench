#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_2__* dev; } ;
struct phy_device {TYPE_1__* drv; } ;
struct TYPE_4__ {struct phy_device* phydev; } ;
struct TYPE_3__ {int (* rxtstamp ) (struct phy_device*,struct sk_buff*,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 unsigned int PTP_CLASS_NONE ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,scalar_t__) ; 
 scalar_t__ likely (int (*) (struct phy_device*,struct sk_buff*,unsigned int)) ; 
 unsigned int ptp_classify_raw (struct sk_buff*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int stub1 (struct phy_device*,struct sk_buff*,unsigned int) ; 

bool skb_defer_rx_timestamp(struct sk_buff *skb)
{
	struct phy_device *phydev;
	unsigned int type;

	if (!skb->dev || !skb->dev->phydev || !skb->dev->phydev->drv)
		return false;

	if (skb_headroom(skb) < ETH_HLEN)
		return false;

	__skb_push(skb, ETH_HLEN);

	type = ptp_classify_raw(skb);

	__skb_pull(skb, ETH_HLEN);

	if (type == PTP_CLASS_NONE)
		return false;

	phydev = skb->dev->phydev;
	if (likely(phydev->drv->rxtstamp))
		return phydev->drv->rxtstamp(phydev, skb, type);

	return false;
}