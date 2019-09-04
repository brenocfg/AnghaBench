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
struct dn_scp {scalar_t__ state; scalar_t__ persist; } ;

/* Variables and functions */
 scalar_t__ DN_CD ; 
 scalar_t__ DN_CI ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static void dn_nsp_conn_ack(struct sock *sk, struct sk_buff *skb)
{
	struct dn_scp *scp = DN_SK(sk);

	if (scp->state == DN_CI) {
		scp->state = DN_CD;
		scp->persist = 0;
	}

	kfree_skb(skb);
}