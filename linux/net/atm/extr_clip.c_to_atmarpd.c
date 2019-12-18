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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct atmarp_ctrl {int type; int itf_num; int /*<<< orphan*/  ip; } ;
typedef  enum atmarp_ctrl_type { ____Placeholder_atmarp_ctrl_type } atmarp_ctrl_type ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int EUNATCH ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_force_charge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmarpd ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 struct sock* sk_atm (int /*<<< orphan*/ ) ; 
 struct atmarp_ctrl* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int to_atmarpd(enum atmarp_ctrl_type type, int itf, __be32 ip)
{
	struct sock *sk;
	struct atmarp_ctrl *ctrl;
	struct sk_buff *skb;

	pr_debug("(%d)\n", type);
	if (!atmarpd)
		return -EUNATCH;
	skb = alloc_skb(sizeof(struct atmarp_ctrl), GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;
	ctrl = skb_put(skb, sizeof(struct atmarp_ctrl));
	ctrl->type = type;
	ctrl->itf_num = itf;
	ctrl->ip = ip;
	atm_force_charge(atmarpd, skb->truesize);

	sk = sk_atm(atmarpd);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_ready(sk);
	return 0;
}