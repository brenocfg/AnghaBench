#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sk_data_ready ) (TYPE_1__*) ;int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  atm_force_charge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  sigd ; 
 TYPE_1__* sk_atm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void sigd_put_skb(struct sk_buff *skb)
{
	if (!sigd) {
		pr_debug("atmsvc: no signaling daemon\n");
		kfree_skb(skb);
		return;
	}
	atm_force_charge(sigd, skb->truesize);
	skb_queue_tail(&sk_atm(sigd)->sk_receive_queue, skb);
	sk_atm(sigd)->sk_data_ready(sk_atm(sigd));
}