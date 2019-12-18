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
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct sk_buff {int dummy; } ;
struct nsp_conn_ack_msg {int msgflg; int /*<<< orphan*/  dstaddr; } ;
struct dn_scp {int /*<<< orphan*/  addrrem; } ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 
 struct sk_buff* dn_alloc_skb (struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_nsp_send (struct sk_buff*) ; 
 struct nsp_conn_ack_msg* skb_put (struct sk_buff*,int) ; 

void dn_send_conn_ack (struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);
	struct sk_buff *skb = NULL;
	struct nsp_conn_ack_msg *msg;

	if ((skb = dn_alloc_skb(sk, 3, sk->sk_allocation)) == NULL)
		return;

	msg = skb_put(skb, 3);
	msg->msgflg = 0x24;
	msg->dstaddr = scp->addrrem;

	dn_nsp_send(skb);
}