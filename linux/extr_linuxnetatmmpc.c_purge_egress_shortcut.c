#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int /*<<< orphan*/  truesize; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  eg_info; } ;
struct k_message {TYPE_1__ content; int /*<<< orphan*/  type; } ;
struct atm_vcc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctrl_info; } ;
typedef  TYPE_2__ eg_cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PLANE_PURGE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_force_charge (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct sock* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void purge_egress_shortcut(struct atm_vcc *vcc, eg_cache_entry *entry)
{
	struct sock *sk;
	struct k_message *purge_msg;
	struct sk_buff *skb;

	dprintk("entering\n");
	if (vcc == NULL) {
		pr_info("vcc == NULL\n");
		return;
	}

	skb = alloc_skb(sizeof(struct k_message), GFP_ATOMIC);
	if (skb == NULL) {
		pr_info("out of memory\n");
		return;
	}

	skb_put(skb, sizeof(struct k_message));
	memset(skb->data, 0, sizeof(struct k_message));
	purge_msg = (struct k_message *)skb->data;
	purge_msg->type = DATA_PLANE_PURGE;
	if (entry != NULL)
		purge_msg->content.eg_info = entry->ctrl_info;

	atm_force_charge(vcc, skb->truesize);

	sk = sk_atm(vcc);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_ready(sk);
	dprintk("exiting\n");
}