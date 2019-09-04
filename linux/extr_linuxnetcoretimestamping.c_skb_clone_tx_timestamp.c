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
struct sk_buff {TYPE_1__* dev; int /*<<< orphan*/  sk; } ;
struct phy_device {TYPE_2__* drv; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* txtstamp ) (struct phy_device*,struct sk_buff*,unsigned int) ;} ;
struct TYPE_3__ {struct phy_device* phydev; } ;

/* Variables and functions */
 unsigned int PTP_CLASS_NONE ; 
 unsigned int classify (struct sk_buff*) ; 
 scalar_t__ likely (int /*<<< orphan*/  (*) (struct phy_device*,struct sk_buff*,unsigned int)) ; 
 struct sk_buff* skb_clone_sk (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct phy_device*,struct sk_buff*,unsigned int) ; 

void skb_clone_tx_timestamp(struct sk_buff *skb)
{
	struct phy_device *phydev;
	struct sk_buff *clone;
	unsigned int type;

	if (!skb->sk)
		return;

	type = classify(skb);
	if (type == PTP_CLASS_NONE)
		return;

	phydev = skb->dev->phydev;
	if (likely(phydev->drv->txtstamp)) {
		clone = skb_clone_sk(skb);
		if (!clone)
			return;
		phydev->drv->txtstamp(phydev, clone, type);
	}
}