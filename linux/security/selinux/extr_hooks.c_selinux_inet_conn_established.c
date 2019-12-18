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
typedef  scalar_t__ u16 ;
struct sock {scalar_t__ sk_family; struct sk_security_struct* sk_security; } ;
struct sk_security_struct {int /*<<< orphan*/  peer_sid; } ;
struct sk_buff {scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_skb_peerlbl_sid (struct sk_buff*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void selinux_inet_conn_established(struct sock *sk, struct sk_buff *skb)
{
	u16 family = sk->sk_family;
	struct sk_security_struct *sksec = sk->sk_security;

	/* handle mapped IPv4 packets arriving via IPv6 sockets */
	if (family == PF_INET6 && skb->protocol == htons(ETH_P_IP))
		family = PF_INET;

	selinux_skb_peerlbl_sid(skb, family, &sksec->peer_sid);
}