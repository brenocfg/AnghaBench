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
struct sk_buff {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_rmem_release (struct sock*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udp_skb_truesize (struct sk_buff*) ; 

void udp_skb_destructor(struct sock *sk, struct sk_buff *skb)
{
	prefetch(&skb->data);
	udp_rmem_release(sk, udp_skb_truesize(skb), 1, false);
}