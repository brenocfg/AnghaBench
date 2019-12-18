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

/* Variables and functions */
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int l2tp_udp_encap_recv (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int pppol2tp_backlog_recv(struct sock *sk, struct sk_buff *skb)
{
	int rc;

	rc = l2tp_udp_encap_recv(sk, skb);
	if (rc)
		kfree_skb(skb);

	return NET_RX_SUCCESS;
}