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
struct sk_buff {scalar_t__ len; struct net_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct atm_vcc {scalar_t__ (* send ) (struct atm_vcc*,struct sk_buff*) ;} ;
struct TYPE_4__ {struct atm_vcc* vcc; } ;

/* Variables and functions */
 TYPE_2__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  atm_account_tx (struct atm_vcc*,struct sk_buff*) ; 
 scalar_t__ stub1 (struct atm_vcc*,struct sk_buff*) ; 

__attribute__((used)) static void
lec_send(struct atm_vcc *vcc, struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;

	ATM_SKB(skb)->vcc = vcc;
	atm_account_tx(vcc, skb);

	if (vcc->send(vcc, skb) < 0) {
		dev->stats.tx_dropped++;
		return;
	}

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
}