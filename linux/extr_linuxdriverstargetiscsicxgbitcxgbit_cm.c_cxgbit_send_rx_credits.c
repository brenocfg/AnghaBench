#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  cdev; } ;
struct cxgbit_sock {TYPE_1__ com; } ;

/* Variables and functions */
 scalar_t__ CSK_STATE_ESTABLISHED ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbit_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void cxgbit_send_rx_credits(struct cxgbit_sock *csk, struct sk_buff *skb)
{
	if (csk->com.state != CSK_STATE_ESTABLISHED) {
		__kfree_skb(skb);
		return;
	}

	cxgbit_ofld_send(csk->com.cdev, skb);
}