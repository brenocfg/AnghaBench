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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct audit_netlink_list {int /*<<< orphan*/  net; int /*<<< orphan*/  portid; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_ctl_lock () ; 
 int /*<<< orphan*/  audit_ctl_unlock () ; 
 struct sock* audit_get_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct audit_netlink_list*) ; 
 int /*<<< orphan*/  netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ ) ; 

int audit_send_list(void *_dest)
{
	struct audit_netlink_list *dest = _dest;
	struct sk_buff *skb;
	struct sock *sk = audit_get_sk(dest->net);

	/* wait for parent to finish and send an ACK */
	audit_ctl_lock();
	audit_ctl_unlock();

	while ((skb = __skb_dequeue(&dest->q)) != NULL)
		netlink_unicast(sk, skb, dest->portid, 0);

	put_net(dest->net);
	kfree(dest);

	return 0;
}