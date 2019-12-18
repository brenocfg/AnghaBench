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
struct sk_buff {int dummy; } ;
struct atmsvc_msg {int /*<<< orphan*/  type; int /*<<< orphan*/  reply; int /*<<< orphan*/  qos; } ;
struct atm_vcc {TYPE_2__* dev; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* change_qos ) (struct atm_vcc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  ATM_VF_RELEASED ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_error ; 
 int /*<<< orphan*/  as_okay ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  sigd_put_skb (struct sk_buff*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void modify_qos(struct atm_vcc *vcc, struct atmsvc_msg *msg)
{
	struct sk_buff *skb;

	if (test_bit(ATM_VF_RELEASED, &vcc->flags) ||
	    !test_bit(ATM_VF_READY, &vcc->flags))
		return;
	msg->type = as_error;
	if (!vcc->dev->ops->change_qos)
		msg->reply = -EOPNOTSUPP;
	else {
		/* should lock VCC */
		msg->reply = vcc->dev->ops->change_qos(vcc, &msg->qos,
						       msg->reply);
		if (!msg->reply)
			msg->type = as_okay;
	}
	/*
	 * Should probably just turn around the old skb. But the, the buffer
	 * space accounting needs to follow the change too. Maybe later.
	 */
	while (!(skb = alloc_skb(sizeof(struct atmsvc_msg), GFP_KERNEL)))
		schedule();
	*(struct atmsvc_msg *)skb_put(skb, sizeof(struct atmsvc_msg)) = *msg;
	sigd_put_skb(skb);
}