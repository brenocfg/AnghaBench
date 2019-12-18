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
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct atm_vcc {TYPE_2__* dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  (* push ) (struct atm_vcc*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* close ) (struct atm_vcc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_CLOSE ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  atm_dev_put (TYPE_2__*) ; 
 int /*<<< orphan*/  atm_return (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 struct atm_vcc* atm_sk (struct sock*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*) ; 
 int /*<<< orphan*/  stub2 (struct atm_vcc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcc_remove_socket (struct sock*) ; 

__attribute__((used)) static void vcc_destroy_socket(struct sock *sk)
{
	struct atm_vcc *vcc = atm_sk(sk);
	struct sk_buff *skb;

	set_bit(ATM_VF_CLOSE, &vcc->flags);
	clear_bit(ATM_VF_READY, &vcc->flags);
	if (vcc->dev) {
		if (vcc->dev->ops->close)
			vcc->dev->ops->close(vcc);
		if (vcc->push)
			vcc->push(vcc, NULL); /* atmarpd has no push */
		module_put(vcc->owner);

		while ((skb = skb_dequeue(&sk->sk_receive_queue)) != NULL) {
			atm_return(vcc, skb->truesize);
			kfree_skb(skb);
		}

		module_put(vcc->dev->ops->owner);
		atm_dev_put(vcc->dev);
	}

	vcc_remove_socket(sk);
}