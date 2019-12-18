#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct dsa_switch {TYPE_2__* ops; } ;
struct dsa_slave_priv {TYPE_1__* dp; } ;
struct TYPE_6__ {struct sk_buff* clone; } ;
struct TYPE_5__ {scalar_t__ (* port_txtstamp ) (struct dsa_switch*,int /*<<< orphan*/ ,struct sk_buff*,unsigned int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  index; struct dsa_switch* ds; } ;

/* Variables and functions */
 TYPE_3__* DSA_SKB_CB (struct sk_buff*) ; 
 unsigned int PTP_CLASS_NONE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned int ptp_classify_raw (struct sk_buff*) ; 
 struct sk_buff* skb_clone_sk (struct sk_buff*) ; 
 scalar_t__ stub1 (struct dsa_switch*,int /*<<< orphan*/ ,struct sk_buff*,unsigned int) ; 

__attribute__((used)) static void dsa_skb_tx_timestamp(struct dsa_slave_priv *p,
				 struct sk_buff *skb)
{
	struct dsa_switch *ds = p->dp->ds;
	struct sk_buff *clone;
	unsigned int type;

	type = ptp_classify_raw(skb);
	if (type == PTP_CLASS_NONE)
		return;

	if (!ds->ops->port_txtstamp)
		return;

	clone = skb_clone_sk(skb);
	if (!clone)
		return;

	DSA_SKB_CB(skb)->clone = clone;

	if (ds->ops->port_txtstamp(ds, p->dp->index, clone, type))
		return;

	kfree_skb(clone);
}