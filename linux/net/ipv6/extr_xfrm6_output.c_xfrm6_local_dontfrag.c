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
struct sock {scalar_t__ sk_family; int sk_protocol; } ;
struct sk_buff {struct sock* sk; } ;
struct TYPE_2__ {int dontfrag; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int IPPROTO_RAW ; 
 int IPPROTO_UDP ; 
 TYPE_1__* inet6_sk (struct sock*) ; 

__attribute__((used)) static int xfrm6_local_dontfrag(struct sk_buff *skb)
{
	int proto;
	struct sock *sk = skb->sk;

	if (sk) {
		if (sk->sk_family != AF_INET6)
			return 0;

		proto = sk->sk_protocol;
		if (proto == IPPROTO_UDP || proto == IPPROTO_RAW)
			return inet6_sk(sk)->dontfrag;
	}

	return 0;
}