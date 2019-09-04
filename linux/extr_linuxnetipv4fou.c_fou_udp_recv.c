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
struct udphdr {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct fou {int protocol; } ;

/* Variables and functions */
 struct fou* fou_from_sock (struct sock*) ; 
 scalar_t__ fou_recv_pull (struct sk_buff*,struct fou*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static int fou_udp_recv(struct sock *sk, struct sk_buff *skb)
{
	struct fou *fou = fou_from_sock(sk);

	if (!fou)
		return 1;

	if (fou_recv_pull(skb, fou, sizeof(struct udphdr)))
		goto drop;

	return -fou->protocol;

drop:
	kfree_skb(skb);
	return 0;
}